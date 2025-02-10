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
	fmt.Println("Part 2 : ", part2(lines))
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
		str := "0"
		if len(numberString[i]) > 0 {
			str = string(numberString[i][0]) + string(numberString[i][len(numberString[i])-1])
		}
		number, err := strconv.Atoi(str)
		if err != nil {
			panic(err)
		}
		sum += number
	}
	return sum
}

func part2(lines []string) int {
	res := 0
	for i := 0; i < len(lines)-1; i++ {
		res += parseLetterNumber(lines[i])
	}
	return res
}

func parseLetterNumber(line string) int {
	maxNumberMap := map[string]int{
		"1":     -1,
		"2":     -1,
		"3":     -1,
		"4":     -1,
		"5":     -1,
		"6":     -1,
		"7":     -1,
		"8":     -1,
		"9":     -1,
		"one":   -1,
		"two":   -1,
		"three": -1,
		"four":  -1,
		"five":  -1,
		"six":   -1,
		"seven": -1,
		"eight": -1,
		"nine":  -1,
	}
	minNumberMap := map[string]int{
		"1":     -1,
		"2":     -1,
		"3":     -1,
		"4":     -1,
		"5":     -1,
		"6":     -1,
		"7":     -1,
		"8":     -1,
		"9":     -1,
		"one":   -1,
		"two":   -1,
		"three": -1,
		"four":  -1,
		"five":  -1,
		"six":   -1,
		"seven": -1,
		"eight": -1,
		"nine":  -1,
	}

	for key := range maxNumberMap {
		if strings.Contains(line, key) {
			maxNumberMap[key] = strings.LastIndex(line, key)
			minNumberMap[key] = strings.Index(line, key)
		}
	}

	maxKey := max(maxNumberMap)
	minKey := min(minNumberMap)

	if minKey == "" {
		minKey = maxKey
	}
	if maxKey == "" {
		maxKey = minKey
	}
	stringNumber := parseNumber(minKey) + parseNumber(maxKey)
	res, err := strconv.Atoi(stringNumber)
	if err != nil {
		panic(err)
	}

	return res
}

func parseNumber(number string) string {
	res := ""
	switch {
	case number == "one":
		res = "1"
	case number == "two":
		res = "2"
	case number == "three":
		res = "3"
	case number == "four":
		res = "4"
	case number == "five":
		res = "5"
	case number == "six":
		res = "6"
	case number == "seven":
		res = "7"
	case number == "eight":
		res = "8"
	case number == "nine":
		res = "9"
	default:
		res = number
	}
	return res
}

func min(numberMap map[string]int) string {
	for key := range numberMap {
		if numberMap[key] == -1 {
			numberMap[key] = 100000
		}
	}
	minKey := "1"
	for key := range numberMap {
		if numberMap[key] != -1 {
			if numberMap[minKey] > numberMap[key] {
				minKey = key
			}
		}
	}
	return minKey
}

func max(numberMap map[string]int) string {
	minKey := ""
	for key := range numberMap {
		if numberMap[minKey] < numberMap[key] {
			minKey = key
		}
	}
	return minKey
}

func isDigit(char string) bool {
	return (char == "1") || (char == "2") ||
		(char == "3") || (char == "9") ||
		(char == "4") || (char == "5") ||
		(char == "6") || (char == "7") ||
		(char == "8") || (char == "0")
}
