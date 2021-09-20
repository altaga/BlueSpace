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
  - [Device:](#device)
  - [WebPage:](#webpage)
- [Field Test:](#field-test)
- [EPIC DEMO:](#epic-demo)

# Introduction:

 Maintain the recommended distance of 1 - 2 meters by means of a simple and fast implementation system without having high infrastructure costs.

# Solution:

I build a BT and BLE signal monitoring system that can detect the distance between one person and another by doing an analysis of the signal strength. In addition to being able to give the user a risk score on the exposure they have had to several people.

In addition to giving a daily exposure analysis through a website.

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

Fortunately, the M5Core2 has many frameworks to be able to program them, however since my greater knowledge and code snippets have been done in the Arduino IDE. I took advantage of the Arduino support of the device to develop the solution more efficiently.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b6/Arudino_Logo.svg/1200px-Arudino_Logo.svg.png">

Install the ESP32 board support and the M5Core2 library to start working with the Arduino IDE.

1. Arduino IDE - [Program Link](https://www.arduino.cc/en/software)
2. Arduino M5Core2 Library - [Library Link](https://github.com/m5stack/M5Core2)

Although the Arduino IDE already comes with several examples to use the board, I leave several optimized and improved codes for you to get used to programming on this board.

[Test Sketches](https://github.com/altaga/BlueSpace/tree/main/Arduino%20Test%20Sketch)

Video:
[![DEMO](./Images/logo.png)](https://youtu.be/wViDAwuF3z8)

Warning: The compilation of the code in Arduino can take up to 5 min, do not despair if the first compilation is taking long haha.

## Main Code:

The BlueSpace core code does the following:

<img src="./Images/softDiagram.png">

There are two main reasons for using a JSON format:

1. When scanning BT devices, it is normal to obtain two or more detections of the same device, when saving it in JSON it allows us to use the Address as a Key, which will eliminate multiple references.

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

2. In the Backend and Frontend of the application, the json format allows easier manipulation and organization of data.


To configure the credentials of the [certs.h](https://github.com/altaga/BlueSpace/blob/main/Arduino%20Code/BlueSpace/certs.h) file, please go to this section [AWS IoT Thing Creation](#create-a-thing)

# AWS Services:

All the Cloud services used were exclusively from AWS for the development of the app, you do not need previous experience for this tutorial, however we recommend reading all the documentation of the services that we are going to use to avoid being confused with any term.

[AWS All Link](#cloud-services)

The services used are divided into two large branches, the services that the device uses mainly and the services that the WebApp uses to consume AWS.

## Device Services:

### AWS IoT:

This service is mainly intended to be able to communicate to our device in a secure way with AWS, this is done through MQTTS, that is, a subscription service and publication of data through topics.

<img src="https://www.luisllamas.es/wp-content/uploads/2019/02/protocolos-iot-pubsub.png">

In this case, our device will be the publisher, as you can see in the main code.

    client.publish(AWS_IOT_TOPIC, string2char(output1));

In order to establish the connection correctly with AWS, a system of 2 certificates and a private Key are used that identify the device to AWS when we send messages to an Endpoint in HTTPS.

<img src="./Images/mqtts.png">

#### Create a Thing:

The steps to create a thing are currently very simple, first we must enter the AWS IoT Core service from the AWS Management Console.

<img src="./Images/iot1.png">

Now we will create our thing, if it is the first time you create one, things should not appear as shown on the screen.

<img src="./Images/iot2.png">

With AWS it is possible to create a whole brigade of devices at the same time, however for this project we will only need to create one.

<img src="./Images/iot3.png">

As we can see in the following menu, we will see that we can configure many characteristics of things in order to be able to create categories, allowed digits between things, etc. However, we will only name our thing and press next at the bottom of the screen.

<img src="./Images/iot4.png">

I highly recommend that you let AWS create the certify and manage them, so we leave the configuration that AWS offers us as recommended and click Next.

<img src="./Images/iot5.png">

So that our device can send data correctly to AWS we must add a policy which allows this correctly.

<img src="./Images/iot6.png">

The policy that we must implement for this prototype without any complications is going to be the following.

<img src="./Images/iot7.png">

When creating the Thing AWS will give us all the necessary certificates, download them all.

<img src="./Images/iot8.png">

With this, the only data that we would need to configure our device would be the AWS Endpoint, however that is in the Settings section.

<img src="./Images/iot9.png">

So you should see the data arrive on your monitor in AWS.

<img src="./Images/mqtt.gif">

### AWS DynamoDB:

Since we can send data to AWS, we cannot let it go to waste, we must analyze the data to be able to do an exposure tracing later in our app. So, as a first step we will now go to the DynamoDB service and create a DB with the following characteristics.

<img src="./Images/db1.png">

We just have to remember the name of the DB for the next step.

<img src="./Images/db2.png">

### AWS IoT Rule:

The simplest way to store the data we receive in the cloud automatically, is through an IoT Rule, this rule is a process that will be executed every time we receive a message in our Topic, as a serverless function. To create the rule we must go to the AWS IoT rules section.

<img src="./Images/rule1.png">

We will create our rule only by placing the name we want and putting the following in the Rule query statement section.

<img src="./Images/rule2.png">

The rule requires that we configure an action that will occur each data entry, in this case it will be the following.

<img src="./Images/rule3.png">

Within this action the required configuration will be the following.

<img src="./Images/rule4.png">

Once we finish this configuration, we will have the action of uploading data to the DB automatically.

<img src="./Images/rule5.png">

## WebPage Services:

Since we have all the services of the device running and sending data to our DB, now we must consume them in our App to show relevant data.

### AWS Lambda:

As the [Connection Diagram](#connection-diagram) says, the first step to consume the DB will be to create a lambda that performs a reading of the data, in addition, since our app must be able to perform readings by date, we must correctly program a scan of the DB.

In my case my solution was to use python as the Backend of the lambda function.

    import json
    import boto3
    from boto3.dynamodb.conditions import Key

    dynamodb = boto3.resource('dynamodb')

    def lambda_handler(event, context):
        
        table = dynamodb.Table("BlueSpace")
        try:
            response = table.scan(FilterExpression = Key('Time').gte(event["headers"]["first"]) & Key('Time').lte(event["headers"]["last"]))
            return(response['Items'])
        except:
            return("Error")

We will notice that the code contains the reference of event ["headers]["ANY_LABEL"], this will make that API Gateway can send the variables in the headers.

### AWS API Gateway:

In order to consume the lambda function from our website, we must create an API that we can call from the app.

<img src="./Images/api1.png">

We put the name we want to our API and we give it next until it is created.

<img src="./Images/api2.png">

Once we have our API, we will have to create a route, which will be the "path" to which you will make the call.

<img src="./Images/api3.png">

The integration of Lambda in the API will be the following.

<img src="./Images/api4.png">

NOTE: When adding the Lambda integration to our API Gateway, the permissions will be automatically configured.

#### Postman Test:

To test that our API is working, we will use some software to test the request like Postman. If we put two dates in the API, our scan will return as the image shows.

<img src="./Images/api5.png">

#### CORS:

Now if we want to consume the API in our web page we will have to configure the Cross-Origin Resource Sharing as shown in the image, the important part of this configuration is to allow our web pages as Authorized Origin.

<img src="./Images/api6.png">

NOTE: without this we will not be able to consume the API from the web page.

### AWS S3:

In order to deploy the web app to the entire internet, we must create an S3 bucket, which will be in charge of storing the files of the web page and performing the static web site hosting.

<img src="./Images/s3-1.png">

Being an application made with the ReactJS framework, it is only necessary to place the files inside the bucket by dragging them.

<img src="./Images/s3-2.png">

In the properties section we can activate the static website hosting, this will give us a URL which we can access from anywhere in the world, however for the deployment of an application to production, this alone is NOT enough.

### AWS CloudFront:

With this service we can ensure that our page obtains an SSL certificate and give us the benefits of the [CDN](https://aws.amazon.com/cloudfront/?nc1=h_ls).

<img src="./Images/cdn.png">

Since this service works without problem, we will be able to see our web page running, with access to the api that we created and with its SSL certificate.

<img src="./Images/cdn1.png">

Feel free to enter the page and explore my history of exposure to people in my day to day.

WebPage: https://d628z7yj7y4ti.cloudfront.net/

# Final Product:

## Device:
<img src="./Images/product1.jpg">
<img src="./Images/product2.jpg">

## WebPage:

<img src="./Images/cdn1.png" width="600px">
<img src="./Images/cdn2.png" width="200px">

# Field Test:

To test that the device worked in a real environment, I did a field test with the device on my weekly visit to the supermarket. 

[![FIELD](./Images/logo.png)](https://youtu.be/Wrq1BNmZRns)

# DEMO:

[![DEMO](./Images/logo.png)](https://youtu.be/gp_sZPsd5kc)
