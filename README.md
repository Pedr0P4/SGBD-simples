<h1 align="center">SGBD (Sistema de Gerenciamento de Banco de Dados) simples</h1>

<p>
  Data Base Management System ou Sistema de Gerenciamento de Banco de Dados (SGBD) é um conjunto de software utilizado para o gerenciamento de uma base de dados, responsáveis por controlar, acessar, organizar e proteger as informações de uma aplicação, 
  tendo como principal objetivo gerenciar as bases de dados utilizadas por aplicações clientes e remover esta responsabilidade das mesmas.
</p>

<br>

<p>
  O SGBD feito por mim em um projeto de faculdade utiliza da organização em tabelas para armazenar os dados, na qual, há colunas e linhas para organizar essas informações.
  Sendo assim, o usuário define quantas colunas terão (depende de quantas informações ele deseja armazenar), e essas colunas terão o nome dos dados que serão armazenados (por exemplo: "Nome", "Idade", "Altura", "Preço", etc.), 
  mas há uma coluna que serve como identificação para uma linha (ou tupla), e essa coluna se chama <b>Chave Primária</b>.
</p>

<br>

<p>
  Tendo a Chave Primária definida (no meu programa é possível dar um nome à sua chave primária, por exemplo, "ID", "Chave", "Matrícula", etc.) e também os nomes das colunas (dependendo de quantas colunas tenham sido criadas),
  basta criar uma linha com as informações de cada coluna, criando assim, um registro.
</p>

<br>

<!-- Imagem "escondida" para exemplo visual -->
<details>
  <summary>❓Exemplo visual</summary>
  <img src="https://lh4.googleusercontent.com/--p0O33vpEHk/TW6Prv4vFZI/AAAAAAAAAAc/kL7GeA4oXno/s1600/estrutura+tabela+sgbd.png">
</details>

<br>

<p>
  Segue abaixo uma imagem de exemplo de uma tabela criada pelo meu programa:
</p>

<br>

<!-- Imagem da tabela feita pelo meu programa (pode mudar futuramente) -->
<img src="https://media.discordapp.net/attachments/1214968443875365028/1214968464247226398/image.png?ex=65fb0a8e&is=65e8958e&hm=754543f29af72905d8fc7c2c7da5d79a04c1e3bead3ca4ae1f3c39830f892daa&=&format=webp&quality=lossless">

<br>
<br>

| Comando | Função |
|---|---|
| `1` | Cria a tabela com atribuição de nome, quantas colunas terá, o nome das colunas, o tipo de dado que irão armazenar (string/char/int/float/double) e o nome da coluna da chave-primária. |
| `2` | Lista as tabelas existentes no diretório que o programa está (as tabelas que o usuário criou). |
| `3` | Cria uma linha (Tupla ou Registro) com os dados das colunas que o usuário definiu no `comando 1`, juntamente com o número da chave-primária (apenas valores int). |
| `4` | Lista os dados criados até agora pelo usuário no formato da imagem apresentada anteriormente. |
| `5` | Pesquisa o dado de uma tabela específica (da escolha do usuário) que o usuário quiser. |
| `6` | Apaga uma linha (Tupla ou Registro) de uma tabela específica (escolhida pelo usuário). |
| `7` | Apaga uma tabela da escolha do usuário. |
| `-1` | Apaga uma tabela. |

<br>
<br>
