# BlueSpace

<img src="./Images/logo.png">

# Table of Contents:

- [BlueSpace](#bluespace)
- [Table of Contents:](#table-of-contents)
- [Introduction:](#introduction)
- [Solution:](#solution)
- [Materials:](#materials)
  - [Hardware:](#hardware)
  - [Software:](#software)
  - [Cloud Services:](#cloud-services)
- [Connection Diagram:](#connection-diagram)
- [M5 Core2 AWS Setup:](#m5-core2-aws-setup)
  - [Main Code:](#main-code)
- [AWS Services:](#aws-services)
  - [Device Services:](#device-services)
    - [AWS IoT:](#aws-iot)
      - [Create a Thing:](#create-a-thing)
    - [AWS DynamoDB:](#aws-dynamodb)
    - [AWS IoT Rule:](#aws-iot-rule)
  - [WebPage Services:](#webpage-services)
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

## Hardware:

1. M5Stack Core2 ESP32 IoT Development Kit for AWS IoT EduKit - [Product Link](https://shop.m5stack.com/collections/stack-series/products/m5stack-core2-esp32-iot-development-kit-for-aws-iot-edukit)

## Software:

1. Arduino IDE - [Program Link](https://www.arduino.cc/en/software)
2. Arduino M5Core2 Library - [Library Link](https://github.com/m5stack/M5Core2)

## Cloud Services:

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

## Main Code:

El codigo principal de BlueSpace realiza lo siguiente:

<img src="./Images/softDiagram.png">

El utilizar un formato JSON tiene dos motivos principales:

1. Al realizar el escaneo de dispositivos de BT, es normal obtener dos o mas detecciones del mismo dispositivo, al guardarlo en JSON nos permite usar la Address como una Key, la cual eliminara las refrencias multiples.

        class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
            void onResult(BLEAdvertisedDevice advertisedDevice) {
              doc[getAddress(advertisedDevice.toString().c_str())][0] = advertisedDevice.getRSSI();
              // Device Address as a JSON Key
              doc[getAddress(advertisedDevice.toString().c_str())][1] = dist(advertisedDevice.getRSSI());
              // Saving the distance
              if (minDist >= dist(advertisedDevice.getRSSI())) {
                minDist = dist(advertisedDevice.getRSSI());
              }
            }
        };

2. En el Backend y en Frontend de la aplicacion el formato json permite una manipulacion y organizacion de datos mas sencilla.

// Realizar video en la barranca de BT para mostrar mejor el funcionamiento.

Para configurar las credenciales del archivo certs.h favor de ir a la seccion [AWS IoT Thing Creation](#create-a-thing)

# AWS Services:

Todos los servicios de Cloud usados fueron exclusivamente de AWS para el desarrollo de la app, no necesitas experiencia previa para este tutorial, sin embargo recomendamos leer toda la documentacion de los servicios que vamos a utilizar para evitar que te confundas con algun termino.

[AWS All Link](#cloud-services)

Los servicios utilizados los dividi en dos grandes ramas, los servicios que utiliza el device principalmente y los servicios que utiliza la WebApp para consumir AWS.

## Device Services:

### AWS IoT:

Este servicio es principalmente destinado a poder comunicar a nuestro device de forma segura con AWS, esto se realiza mediante MQTTS, osea un servicio de suscripbion y publicacion de datos a traves de topicos.

<img src="https://www.luisllamas.es/wp-content/uploads/2019/02/protocolos-iot-pubsub.png">

En este caso nuestro device sera el publisher, como se puede ver en el codigo principal.

    client.publish(AWS_IOT_TOPIC, string2char(output1));

Para poder establecer la conexion correctamente con AWS se utiliza un sistema de 2 certificados y una private Key que identifican al device ante AWS cuando mandamos mensajes a un Endpoint en HTTPS.

<img src="./Images/mqtts.png">

#### Create a Thing:

Los pasos para poder crear una thing son actualmente muy sencillos, primero deberemos entrar al servicio AWS IoT Core desde AWS Management Console.

<img src="./Images/iot1.png">

Ahora crearemos nuestra thing, si es la primera vez que creas una no deberian aparecer things como se muestra en pantalla.

<img src="./Images/iot2.png">

Con AWS es posible crear toda una brigada de devices a la vez, sin embargo para este proyecto solo necesitaremos crear una.

<img src="./Images/iot3.png">

Como podemos ver en el siguiente menu, veremos que podemos configurar muchas caracteristicas de las things con el fin de poder crear categorias, permidos dintitos entre things, etc. Sin embargo solo le pondremos el nombre a nuestra thing y presionaremos next al fondo de la pantalla.

<img src="./Images/iot4.png">

Recomiendo ampliamente que dejen a AWS crear los certificarlos y gestionarlos, asi que dejamos la configuracion que nos ofrece AWS como recommended y presionamos Next.

<img src="./Images/iot5.png">

Para que nuestro device pueda mandar datos correctamente a AWS deberemos agregar una policy la cual permita esto correctamente.

<img src="./Images/iot6.png">

La policy que debemos implementar para este prototipo sin ninguna complicacion va a ser la siguiente.

<img src="./Images/iot7.png">

Al momento de crear la Thing AWS nos dara todos los certificados necesarios, descargalos todos.

<img src="./Images/iot8.png">

Con esto el unico dato que nos faltaria para configurar nuestro device seria el Endpoint de AWS, sin embargo ese se encuentra en la seccion de Settings.

<img src="./Images/iot9.png">

### AWS DynamoDB:



### AWS IoT Rule:

## WebPage Services:

### AWS Lambda:

### AWS API Gateway:

#### Postman Test:

#### CORS:

### AWS S3:

### AWS CloudFront:

# Final Product:

# Field Test:

# EPIC DEMO: