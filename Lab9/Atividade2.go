// introduz canais na aplicação Go
package main

import (
	"fmt"
	"time"
)

func tarefa(str chan string) {
	//escreve no canal
	var msgA = ""
	msgA = <-str
	fmt.Println(msgA)
	str <- "Oi Main, bom dia, tudo bem?"
	msgA = <-str
	fmt.Println(msgA)
	str <- "Certo, entendido."

	fmt.Printf("Finalizando tarefa \n")

}
func main() {
	var msg = "" //string vazia

	//cria um canal de comunicacao nao-bufferizado
	str := make(chan string)
	//cria um goroutine que executará a função 'tarefa'
	go tarefa(str)

	str <- "Ola, Goroutine, bom dia!"
	msg = <-str

	fmt.Println(msg)

	//lê do canal
	str <- "Tudo bem! Vou terminar tá?"
	msg = <-str
	fmt.Println(msg)
	fmt.Printf(" Finalizando main \n")
	time.Sleep(time.Second) //bloqueio na main

}
