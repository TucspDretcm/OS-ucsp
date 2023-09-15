#!/bin/bash

P1="./P1"
P2="./P2"

for i in {1..10}
do
  echo "$i ------------->"
  # &: Ejecuta el archivo en segundo plano y almacena el PID en una variable
  $P1 &
  pid=$! #$! es una variable especial que contiene el PID (identificador de proceso) del comando que se ejecutó en segundo plano.
  # Enviar la señal SIGUSR1 al proceso con el PID actual de "P1"
  sleep 1
  kill -SIGUSR1 $pid
  sleep 1
  $P2 &
  # Espera un segundo antes de continuar
  sleep 1
done

