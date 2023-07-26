# tch-rs-example MNIST

Nesse tutorial você irá aprender a usar a partição **gpu** e rust  para treinar um modelo de deep learning para resolver o [MNIST](http://yann.lecun.com/exdb/mnist/).

[TOC]

## Instalando dependências

Primeiro instale o rust toolchain na sua pasta HOME, no nó de login.

```bash
$ curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

segundo crie um novo projeto rust com cargo chamado pytorch-example. Para esse projeto Adicione as dependências:

- **anyhow**, uma biblioteca para facilita o tratamento de erro em rust
- **tch** O framework Pytorch para criação de modelos deep learning escrito em C++, mas com bindings para rust

```bash
cargo new pytorch-example
cd pytorch-example
cargo add anyhow
cargo add tch
```

## Criando um aplicação em rust para treinar uma rede neural

A aplicação escrita  em rust, deverá selecionar qual dispositivo de processamento, CPU ou GPU, deverá ser usado para a execução dos cálculos numéricos.
Carregar o conjunto de dados MNIST para ser computado em tal dispositivo. Criar um modelo deep learning e treinar o modelo. Portanto podemos entender
a aplicação em  4 partes importantes:  carregamento do conjunto de dados MNIST, configuração do dispositivo, criando um modelo deep learning, treinamento.

## Carregamento do conjunto de dados MNIST

Como o MNIST é um conjunto de dados muito famoso, o próprio pytorch possui mecanismos de carregá-lo, desde que você tenha ele baixado e descompactado.
Para baixar o dataset, você pode criar um script similar ao [get_inputs.sh](https://github.com/samuel-cavalcanti/tch-rs-example/blob/main/get_inputs.sh). Onde basicamente ele cria o diretório chamado **data**
e baixa os arquivos do dataset e os extrai com **gunzip**

```bash
#!/bin/bash 
# get_inputs.sh
mkdir data -p
cd data
wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz; gunzip train-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz; gunzip train-labels-idx1-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz; gunzip t10k-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz; gunzip t10k-labels-idx1-ubyte.gz
```

Para carregar o dataset basta usar o a função **tch::vision::mnist::load_dir**

```rust
let dataset = match tch::vision::mnist::load_dir("data") { Dataset
          Ok(d) => d, 
          Err(_) => panic!("Dataset Not found, run the get_inputs.sh !!"),
};
```

### Configuração do dispositivo de processamento

Utilizando um framework pytorch podemos selecionar o dispositivo da seguinte forma, se uma **GPU** estiver disponível, então utilize GPU. Caso o contrário utilize
**CPU**. Com o dispositivo podemos criar um conjunto de tensores cujo seus valores **variam** e que esses valores deverão ser capazes de serem armazenados, ou seja
criamos uma **VarStore**.

```rust
 let device = tch::Device::cuda_if_available();
 let vs = tch::nn::VarStore::new(device.clone());
```

Também precisamos transformar ou mover os dados do conjunto de dados para o dispositivo de processamento

```rust
fn dataset_to_device(dataset: Dataset, device: &Device) -> Dataset {
    let train_labels = dataset.train_labels.to_device(device.clone());
    let train_images = dataset.train_images.to_device(device.clone());
    let test_labels = dataset.test_labels.to_device(device.clone());
    let test_images = dataset.test_images.to_device(device.clone());

    Dataset {
        test_images,
        test_labels,
        train_images,
        train_labels,
        labels: dataset.labels,
    }
}

let dataset = dataset_to_device(dataset, &device);
```

### Criando um modelo deep learning

O modelo deep learning utilizado nesse exemplo será um modelo sequencial simples e com poucas camadas. Em rust o modelo
ficou assim:

```rust
use tch::{nn, nn::Module};
const IMAGE_DIM: i64 = 784;
const HIDDEN_NODES: i64 = 128;
const LABELS: i64 = 10;

fn net(vs: &nn::Path) -> impl Module {
    nn::seq()
        .add(nn::linear(
            vs / "layer1",
            IMAGE_DIM,
            HIDDEN_NODES,
            Default::default(),
        ))
        .add_fn(|xs| xs.relu())
        .add(nn::linear(vs, HIDDEN_NODES, LABELS, Default::default()))
}

let net = net(&vs.root());
```

Observe que vs (VarStore) é passada na função **net**, de modo que criar uma camada, ou módulo (layer) é alocar novos de tensores, para a variável.

### Treinamento

Para treinar uma rede neural, pode-se utilizar vários algoritmos de otimização, porém nesse exemplo foi utilizado o [Adam](https://pytorch.org/docs/stable/generated/torch.optim.Adam.html),
com uma taxa de aprendizado de **0.001**. O modelo será treinado durante 200 interações. Em rust a implementação do treinamento fica da seguinte forma

```rust
let mut opt = nn::Adam::default().build(&vs, 1e-3)?;
   
for epoch in 1..200 {
    let loss = net
            .forward(&dataset.train_images)
            .cross_entropy_for_logits(&dataset.train_labels);
        opt.backward_step(&loss);
        let test_accuracy = net
            .forward(&dataset.test_images)
            .accuracy_for_logits(&dataset.test_labels);
        println!(
            "epoch: {:4} train loss: {:8.5} test acc: {:5.2}% is cuda: {}",
            epoch,
            f64::try_from(&loss)?,
            100. * f64::try_from(&test_accuracy)?,
            device.is_cuda(),
        );
    }
```

Você pode ver a implementação completa em [main.rs](https://github.com/samuel-cavalcanti/tch-rs-example/blob/main/src/main.rs)

## Executando a aplicação com cuda no supercomputador

Atualmente o supercomputador no NPAD possui uma partição chamada **gpu**, nessa partição encontram-se os nós com GPUs bem potentes capazes de executar a aplicação em 1 segundo.

```bash
#!/bin/bash 
#SBATCH --job-name=neural_train
#SBATCH --time=0-0:15
#SBATCH --partition=gpu
#SBATCH --exclusive

# informando ao tch-rs que desejo compilar com cuda na versão 11.7
export TORCH_CUDA_VERSION=cu117

cargo r --release
```

Cargo é o gerenciador de pacotes official da linguagem Rust, perceba que ao executar o comando `cargo r --release`. A aplicação cargo irá compilar a aplicação utilizando flags de otimização e irá executar o programa. Caso tenha compilado a aplicação no nó de login, será necessário remover a pasta **target**, antes de submeter o script

```bash
# rm -rf target # caso tenha compilado a aplicação no nó de login.

sbatch run_on_superpc.sh
```

o script **run_on_superpc.sh** pode ser encontrado [aqui](https://github.com/samuel-cavalcanti/tch-rs-example/blob/main/run_on_superpc.sh). Todo o projeto pode ser encontrado no github [github.com/samuel-cavalcanti/tch-rs-example](https://github.com/samuel-cavalcanti/tch-rs-example)
