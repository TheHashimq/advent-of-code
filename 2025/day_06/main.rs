use std::fs;
use std::time::Instant;

fn main() {
    let input = fs::read_to_string("input.txt").expect("input file missing");
    let lines: Vec<&str> = input.lines().collect();

    let start1 = Instant::now();
    let ans1 = part1(&lines);
    let duration1 = start1.elapsed();
    println!("Part 1: {} (time: {:?})", ans1, duration1);

    let start2 = Instant::now();
    let ans2 = part2(&lines);
    let duration2 = start2.elapsed();
    println!("Part 2: {} (time: {:?})", ans2, duration2);
}
fn parse_input(lines: &[&str]) -> (Vec<Vec<i64>>, Vec<String>) {
    let mut grid: Vec<Vec<i64>> = Vec::new();
    let mut last_row: Vec<String> = Vec::new();
    for (i, line) in lines.iter().enumerate() {
        if i == lines.len() - 1 {
            last_row = line
                .split_whitespace()
                .map(|s| s.to_string())
                .collect();
        } else {
            let row: Vec<i64> = line
                .split_whitespace()
                .map(|s| s.parse::<i64>().unwrap())
                .collect();

            grid.push(row);
        }
    }

    (grid, last_row)
}

fn part1(lines: &[&str]) -> i64 {
    let (grid, last_row) = parse_input(lines);
    let rows = grid.len();
    let cols = grid[0].len();
    let mut column_wise: Vec<Vec<i64>> = Vec::new();
    for col in 0..cols {
        let mut col_values: Vec<i64> = Vec::new();
        for row in 0..rows {
            let num: i64 = grid[row][col];
            col_values.push(num);
        }
        column_wise.push(col_values);
    }
    let mut total: i64 = 0;
    for (index, op) in last_row.iter().enumerate() {
        let column = &column_wise[index];
        let col_result = if op == "+" {
            column.iter().sum::<i64>()
        } else if op == "*" {
            column.iter().product::<i64>()
        } else {
            0
        };
        total += col_result;
    }
    total
}

fn part2(lines: &[&str]) -> i64 {
    if lines.is_empty() {
        return 0;
    }
    let rows = lines.len();
    let cols = lines.iter().map(|l| l.len()).max().unwrap_or(0);
    let mut matrix: Vec<Vec<char>> = Vec::with_capacity(rows);
    for &line in lines {
        let mut row_chars: Vec<char> = line.chars().collect();
        if row_chars.len() < cols {
            row_chars.resize(cols, ' ');
        }
        matrix.push(row_chars);
    }
    let mut total: i64 = 0;
    let mut processed = vec![false; cols];
    for col in 0..cols {
        let op_char = matrix[rows - 1][col];
        if op_char != '+' && op_char != '*' {
            continue;
        }
        if processed[col] {
            continue;
        }
        let operator = op_char;
        let mut end_col = col + 1;
        while end_col < cols {
            if (0..rows).all(|r| matrix[r][end_col] == ' ') {
                break;
            }
            end_col += 1;
        }
        let mut numbers: Vec<i64> = Vec::new();
        for c in (col..end_col).rev() {
            let mut digits = String::new();
            for row in 0..(rows - 1) {
                let ch = matrix[row][c];
                if ch.is_ascii_digit() {
                    digits.push(ch);
                }
            }

            if !digits.is_empty() {
                let number: i64 = digits.parse().unwrap();
                numbers.push(number);
            }
            processed[c] = true;
        }
        if !numbers.is_empty() {
            numbers.reverse();
            let mut result = numbers[0];
            for &num in &numbers[1..] {
                if operator == '+' {
                    result += num;
                } else {
                    result *= num;
                }
            }
            total += result;
        }
    }
    total
}
