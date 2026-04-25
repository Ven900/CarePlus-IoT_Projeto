# CarePlus IoT – Monitoramento de Saúde

## 👨‍🎓 Integrantes

* Bruno Ventura — RM 568316
* Diogo Henrique — RM 568541
* Giovanna P. Zagaroli — RM 567572
* Venicio — RM 568088
* Vinicius Nathan — RM 567105

**Instituição:** FIAP
**Disciplina:** Edge Computing & Computer Systems

---

## 📌 O que é o projeto?

O CarePlus é um sistema que simula um dispositivo de saúde conectado à internet.

Ele utiliza um ESP32 para coletar dados de temperatura, simular batimentos cardíacos e enviar essas informações para a nuvem em tempo real.

👉 Em resumo:
É um sistema simples de saúde que funciona como um “monitor inteligente”.

---

## 🎯 Qual é o objetivo?

Mostrar na prática como funciona um sistema de IoT na área da saúde, utilizando:

* sensores
* internet
* processamento local
* envio de dados para a nuvem

---

## 🔌 O que foi utilizado?

* ESP32 → dispositivo principal
* Sensor DHT22 → mede temperatura
* LED → indica alerta
* Wi-Fi → conecta à internet
* MQTT → envia dados
* HiveMQ → recebe os dados na nuvem

---

## ⚙️ Como o sistema funciona?

O funcionamento acontece em etapas simples:

1. O ESP32 liga e conecta ao Wi-Fi
2. O sensor DHT22 mede a temperatura
3. O sistema simula batimentos cardíacos
4. O ESP32 analisa os dados
5. Se a temperatura for maior que 37.5°C → o LED acende
6. Os dados são enviados para a nuvem

---

## ⚡ O que é Edge Computing nesse projeto?

Edge Computing significa que o sistema toma decisões sozinho, sem depender da internet.

👉 Exemplo:
Se a temperatura está alta → o LED acende imediatamente

Isso é importante porque:

* é mais rápido
* não depende da nuvem
* aumenta a eficiência

---

## ☁️ Como os dados são enviados?

Os dados são enviados usando MQTT, que é um protocolo leve usado em IoT.

O envio é feito com segurança (TLS), através do HiveMQ Cloud.

👉 Isso garante:

* rapidez
* baixo consumo
* segurança dos dados

---

## 📊 Que tipo de dados são enviados?

O sistema envia informações como:

* temperatura
* umidade
* batimentos cardíacos (simulados)
* status de alerta

---

## 🧱 Como é a arquitetura?

ESP32 (dispositivo)
↓
Wi-Fi
↓
MQTT (HiveMQ Cloud)
↓
Sistema de monitoramento

---

## 📁 O que tem no projeto?

* Código do ESP32
* Circuito no Wokwi
* Bibliotecas utilizadas
* Documentação (este arquivo)

---

## 🧪 Onde rodar o projeto?

O projeto pode ser testado no Wokwi, onde é possível simular o circuito e ver o funcionamento em tempo real.

---

## 🎯 Por que esse projeto é importante?

Porque mostra na prática:

* como funciona IoT
* como conectar hardware à internet
* como enviar dados para a nuvem
* como tomar decisões localmente

---

## 🏁 Conclusão

O CarePlus mostra que é possível criar um sistema de monitoramento de saúde usando tecnologias acessíveis, com baixo custo e funcionamento eficiente.

Ele integra sensores, internet e processamento local, simulando uma solução real utilizada na área da saúde.

---
