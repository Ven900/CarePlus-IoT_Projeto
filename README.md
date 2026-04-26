# 🏥 CarePlus IoT

### Monitoramento Inteligente de Saúde com ESP32

---

## Integrantes

* Bruno Ventura — RM 568316
* Diogo Henrique — RM 568541
* Giovanna P. Zagaroli — RM 567572
* Venicio — RM 568088
* Vinicius Nathan — RM 567105

**FIAP – Edge Computing & Computer Systems**

---

##  Visão Geral

O **CarePlus** é um sistema de monitoramento de saúde baseado em IoT (Internet das Coisas), desenvolvido com ESP32.

O sistema coleta dados de temperatura e umidade, simula batimentos cardíacos e envia essas informações para a nuvem em tempo real, utilizando comunicação segura via MQTT (TLS).

Além disso, o dispositivo realiza **processamento local (Edge Computing)**, permitindo respostas imediatas sem depender da internet.

---

##  Objetivo do Projeto

Criar um sistema inteligente que demonstre:

* Monitoramento de saúde em tempo real
* Processamento local (Edge Computing)
* Comunicação segura com a nuvem
* Interação com o usuário

---

## 🧱 Arquitetura da Solução

```
[SENSOR DHT22]
        ↓
[ESP32 - EDGE]
        ↓
[Wi-Fi]
        ↓
[MQTT - HiveMQ Cloud (TLS)]
        ↓
[Aplicação / Dashboard]
```

---

## 🔌 Hardware Utilizado

| Componente | Função                      |
| ---------- | --------------------------- |
| ESP32      | Processamento e comunicação |
| DHT22      | Temperatura e umidade       |
| LED        | Alerta visual               |
| Buzzer     | Alerta sonoro               |
| Botão      | Simulação de BPM            |
| OLED       | Interface de visualização   |

---

## ⚙️ Funcionamento do Sistema

1. ESP32 conecta ao Wi-Fi
2. Sensor coleta dados ambientais
3. BPM é simulado via botão
4. Dados são processados localmente
5. Sistema classifica o estado em:

   * 🟢 NORMAL
   * 🟡 CUIDADO
   * 🟠 ALERTA
   * 🔴 CRÍTICO
6. Alertas são acionados:

   * LED → visual
   * Buzzer → sonoro
7. Dados são exibidos no display OLED
8. Informações são enviadas via MQTT

---

## ⚡ Edge Computing

O sistema realiza decisões diretamente no dispositivo:

✔ Detecção de risco em tempo real
✔ Acionamento imediato de alertas
✔ Independência da nuvem

---

## ☁️ Comunicação

* Protocolo: MQTT
* Broker: HiveMQ Cloud
* Porta: 8883
* Segurança: TLS

---

## 📊 Dados Monitorados

* 🌡️ Temperatura
* 💧 Umidade
* ❤️ BPM (simulado)
* ⚠️ Nível de risco

---

## 📁 Estrutura do Projeto

```
careplus-iot/
│
├── sketch.ino
├── diagram.json
├── libraries.txt
├── README.md
```

---

## 🧪 Simulação

O projeto pode ser executado no Wokwi:

🔗 Adicione aqui o link do Wokwi

---

## 💻 Repositório

Este repositório contém:

* Código completo
* Arquitetura
* Documentação

---

## 🎯 Diferenciais

✔ Edge Computing aplicado
✔ Comunicação segura (TLS)
✔ Interface com display
✔ Sistema de alerta inteligente
✔ Arquitetura IoT completa

---

## 🏁 Conclusão

O CarePlus demonstra como a IoT pode ser aplicada na área da saúde, integrando sensores, processamento local e comunicação em nuvem.

O sistema simula um dispositivo real de monitoramento, com capacidade de resposta em tempo real e estrutura escalável.

---

## 🔮 Possíveis Evoluções

* Dashboard em tempo real (Node-RED)
* Aplicativo mobile
* Histórico de dados
* Integração com IA

---

