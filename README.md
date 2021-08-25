# BlueSpace

<img src="./Images/logo.png">

# Table of Contents:

- [BlueSpace](#bluespace)
- [Table of Contents:](#table-of-contents)
- [Introduction:](#introduction)
- [Solution:](#solution)
- [Materials:](#materials)
- [Connection Diagram:](#connection-diagram)
- [M5 Core2 AWS Setup:](#m5-core2-aws-setup)
- [AWS Services:](#aws-services)
  - [AWS IoT:](#aws-iot)
  - [AWS DynamoDB:](#aws-dynamodb)
  - [AWS IoT Rule:](#aws-iot-rule)
  - [AWS Lambda:](#aws-lambda)
  - [AWS API Gateway:](#aws-api-gateway)
    - [Postman Test:](#postman-test)
    - [CORS:](#cors)
  - [AWS S3:](#aws-s3)
  - [AWS CloudFront:](#aws-cloudfront)
- [Final Product:](#final-product)
- [Field Test:](#field-test)
- [EPIC DEMO:](#epic-demo)

# Introduction:

 Maintain the recommended distance of 1 - 2 meters by means of a simple and fast implementation system without having high infrastructure costs.

# Solution:

I build a BT and BLE signal monitoring system that can detect the distance between one person and another by doing an analysis of the signal strength. In addition to being able to give the user a risk score on the exposure they have had to several people.

Ademas de dar un analisis de exposicion diario mediante una pagina web.

WebPage: https://d628z7yj7y4ti.cloudfront.net/

Differences with existing technologies and why our solution is better:

https://www.briefcam.com/lp/video-role-in-public-health-crisis/?utm_campaign=Health+Crisis+Awareness&utm_medium=ppc&utm_source=adwords&utm_term=social%20distancing%20monitor&hsa_net_90_saad_h2 = 9907271420 & hsa_kw social =% 20distancing% 20monitor & hsa_grp = 105891268772 & hsa_tgt = KWD-899812972242 & hsa_ver = 3 & hsa_acc = 3153374593 & gclid = Cj0KCQjwuJz3BRDTARIsAMg-HxWDhm00pKPyJyV_vBudSjKiK4cs8MS43Kc55Rt8ns_IuZICYjsBRqEaAs1JEALw_wcB

https://www.technologyreview.com/2020/04/17/1000092/ai-machine-learning-watches-social-distancing-at-work/3

Most Ideas need an implementation of video cameras, image processing center, etc.

Our solution has the advantage of not needing to carry out complex video analytics to give distance results.

https://www.unacast.com/covid19/social-distancing-scoreboard

The Disadvantage of those ideas is that they perform an extrapolation of the social distance by country, instead of making a solution based on real data. Which our solution can generate.

Our solution has the advantage of not needing to carry out complex video analytics to give distance results. The advantage of using these simple systems is that they are easily achievable at a large-scale manufacturing level and can prevent the spread of new COVID-19 patients, in addition to generating an enormous amount of information and data on the social distancing of people in real time, added to this we can generate heat maps where we can see crowds and more risk of contagion.

# Materials:

Hardware:

1. M5Stack Core2 ESP32 IoT Development Kit for AWS IoT EduKit - [Product Link](https://shop.m5stack.com/collections/stack-series/products/m5stack-core2-esp32-iot-development-kit-for-aws-iot-edukit)

Software:

1. Arduino IDE - [Program Link](https://www.arduino.cc/en/software)
2. Arduino M5Core2 Library - [Library Link](https://github.com/m5stack/M5Core2)

Cloud Services:

1. IoT Core - [Service Link](https://aws.amazon.com/iot-core/)
2. DynamoDb - [Service Link](https://aws.amazon.com/dynamodb/?nc2=type_a)
3. API Gateway - [Service Link](https://aws.amazon.com/api-gateway/?nc2=type_a)
4. Lambda - [Service Link](https://aws.amazon.com/lambda/?nc2=type_a)
5. S3 - [Service Link](https://aws.amazon.com/s3/?nc2=type_a)
6. CloudFront - [Service Link](https://aws.amazon.com/cloudfront/?nc2=type_a)

# Connection Diagram:

<img src="./Images/diagram.png">

# M5 Core2 AWS Setup:

El M5Core2 por fortuna para mi tiene muchos frameworks para poder programarlos, sin embargo ya que mi mayor conocimiento y code snippets los he realizado en el Arduino IDE, apoveche el soporte de Arduino del dispositivo para desarrollar mas eficientemente la solucion.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b6/Arudino_Logo.svg/1200px-Arudino_Logo.svg.png">

Instala el soporte de las placas ESP32 y la libreria M5Core2 para empezar a trabajar con el Arduino IDE.

1. Arduino IDE - [Program Link](https://www.arduino.cc/en/software)
2. Arduino M5Core2 Library - [Library Link](https://github.com/m5stack/M5Core2)

Aunque el Arduino IDE viene ya con varios ejemplos para utilizar la placa, dejo varios codigos optimizados y mejorados para que te acostumbres a programar en esta placa.

[Test Sketches](https://github.com/altaga/BlueSpace/tree/main/Arduino%20Test%20Sketch)

Video:
[![DEMO](./Images/logo.png)](https://youtu.be/wViDAwuF3z8)

Advertencia: El compilado de el codigo en Arduino puede tardar hasta 5 min, no desesperes si la primera compilacion es tardada.

# AWS Services:

## AWS IoT:

## AWS DynamoDB:

## AWS IoT Rule:

## AWS Lambda:

## AWS API Gateway:

### Postman Test:

### CORS:

## AWS S3:

## AWS CloudFront:

# Final Product:

# Field Test:

# EPIC DEMO: