// Atividade 5 que resolve o problema de encontrar números primos em uma lista de entrada.

// funçao tarefa checa quais numeros são primos através da função é primo, se o numero for primo o valor é colocado no canal resultado. Quando todos os numeros forem processados é enviado um sinal verdadeiro para o canal de termino
package main

import (
	"fmt"
	"math"
)

func tarefa(lista <-chan int, resultado chan<- int, done chan bool) {
	for num := range lista {
		if ehPrimo(num) {
			resultado <- num
		}
	}
	done <- true
}

// A função main define a quantidade de N, números igual a 100 e M goroutines como 4, cria-se também os canais que serão utilizados
func main() {
	N := 100
	M := 4
	lista := make(chan int)
	resultado := make(chan int)
	done := make(chan bool, M) // canal bufferizado

	go func() {
		for i := 2; i <= N; i++ {
			lista <- i
		}
		close(lista)
	}()

	for i := 0; i < M; i++ {
		go tarefa(lista, resultado, done)
	}

	go func() {
		for i := 0; i < M; i++ {
			<-done
		}
		close(resultado)
	}()

	cont := 0
	for primo := range resultado {
		fmt.Println(primo) //print para fins de teste
		cont++
	}

	fmt.Printf("O total de números primos no intervalo: %d\n", cont)
}
func ehPrimo(num int) bool {
	if num <= 1 {
		return false
	}
	if num == 2 {
		return true
	}
	if num%2 == 0 {
		return false
	}
	for i := int(3); i < int(math.Sqrt(float64(num))+1); i += 2 {
		if num%i == 0 {
			return false
		}

	}
	return true

}
