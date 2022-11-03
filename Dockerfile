FROM ubuntu:latest

# install updates and install cron and apt-utils
RUN apt-get update
RUN apt-get install -y python3 python3-distutils python3-pip python3-apt python3-dev

# install dependencies
# influxdb
RUN apt-get install influxdb
RUN apt-get install influxdb-client
# RUN service influxdb start

RUN pip install -r requirements.txt

CMD ["python3 mqtt/MQTTInfluxBridge.py"]

