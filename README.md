# Sistema de Alerta de Desmatamento Local (SADEL)

Este é o repositório do "SADEL", desenvolvido por alunos de Análise e Desenvolvimento de Sistemas da UniFAP. O objetivo é um sistema de monitoramento e alerta de desmatamento e queimadas em tempo real para a região da Chapada do Araripe.

---

## Funcionalidades Principais

* **Detecção de Som:** O protótipo usa um sensor (simulado no Wokwi por um potenciômetro) para identificar padrões sonoros que sugerem o uso de motosserras.
* **Detecção de Queimadas:** Um segundo sensor (também simulado) monitora a fumaça e o gás no ambiente, ativando um alerta imediato em caso de risco de incêndio.
* **Alerta em Tempo Real:** Ao detectar um som suspeito acima de um limite, o sistema envia um pacote de alerta imediatamente para um banco de dados na nuvem (Firebase).
* **Monitoramento de Status:** O sensor envia um "sinal de vida" (heartbeat) a cada 30 segundos para confirmar que está online e funcionando.
* **Dashboard de Visualização:** Um dashboard web simples (feito em HTML/CSS/JS) consome os dados do Firebase e exibe os alertas recebidos.

---

## Tecnologias Utilizadas

Este projeto é dividido em duas partes principais:

### 1. Protótipo (Hardware/IoT)
* ![ESP32](https://img.shields.io/badge/ESP32-E7332E?style=for-the-badge&logo=espressif&logoColor=white)
* ![Arduino](https://img.shields.io/badge/Arduino_(C++)-00979D?style=for-the-badge&logo=arduino&logoColor=white)
* ![Firebase](https://img.shields.io/badge/Firebase-FFCA28?style=for-the-badge&logo=firebase&logoColor=black)
* ![Wokwi](https://img.shields.io/badge/Wokwi-434A54?style=for-the-badge&logo=wokwi&logoColor=white)

### 2. Dashboard (Frontend)
* ![HTML5](https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white)
* ![CSS3](https://img.shields.io/badge/CSS3-1572B6?style=for-the-badge&logo=css3&logoColor=white)
* ![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)

---

## Estrutura do Repositório

O projeto está organizado nas seguintes pastas:

* **/dashboard/**: Contém todos os arquivos do frontend web (HTML, CSS, JS) responsável por exibir os alertas.
* **/sensor\_norte/**: Contém o projeto PlatformIO do **Sensor 1 (Crato)**. Inclui o código-fonte (`src/main.cpp`), o arquivo de configuração (`platformio.ini`), e a definição do circuito (`diagram.json`).
* **/sensor\_sul/**: Contém o projeto PlatformIO do **Sensor 2 (Barbalha)**. Inclui o código-fonte (`src/main.cpp`), o arquivo de configuração (`platformio.ini`), e a definição do circuito (`diagram.json`).
---

## Aviso de Configuração

Para que o projeto funcione, você **DEVE** fornecer suas próprias credenciais. Os arquivos de código foram enviados ao GitHub sem chaves de API, hosts de banco de dados e tokens de autenticação (dados sensíveis). Caso queira testar o projeto, você precisará configurar os seguintes arquivos:

1. Firmware (C++/Sensores): Você precisará criar o arquivo secrets.h nas pastas de cada sensor e inserir suas credenciais de Firebase e Wi-Fi para que o código compile e se conecte à internet.
2. Dashboard (JS): Você precisará substituir os placeholders (SUA_API_KEY_AQUI, etc.) nos arquivos JavaScript (dentro da pasta /dashboard/) para que o site funcione e consuma seu banco de dados.

---
## Autores

* **Evandio de Souza Filho**
    * [LinkedIn](https://www.linkedin.com/in/evandio-de-souza/)
    * [GitHub](https://github.com/evandiopds)

* **João Lucas Batista**
  * [LinkedIn](https://www.linkedin.com/in/jo%C3%A3olucasdev/)
  * [GitHub](https://github.com/joaolucasbatista)

