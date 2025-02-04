package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	data, err := os.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}

	lines := strings.Split(string(data), "\n")
	fmt.Println("Part 1 : ", part1(lines))
}

func part1(lines []string) int {
	numberString := []string{}
	for i := 0; i < len(lines); i++ {
		str := ""
		for j := 0; j < len(lines[i]); j++ {
			if isDigit(string(lines[i][j])) {
				str += string(lines[i][j])
			}
		}
		numberString = append(numberString, str)
	}

	sum := 0
	for i := 0; i < len(numberString)-1; i++ {
		str := string(numberString[i][0]) + string(numberString[i][len(numberString[i])-1])
		number, err := strconv.Atoi(str)
		if err != nil {
			panic(err)
		}
		sum += number
	}
	return sum
}

func isDigit(char string) bool {
	return (char == "1") || (char == "2") ||
		(char == "3") || (char == "9") ||
		(char == "4") || (char == "5") ||
		(char == "6") || (char == "7") ||
		(char == "8") || (char == "0")
}
