use std::fs;

fn main() {
    let input = fs::read_to_string("input.txt").expect("input file missing");
    let lines: Vec<&str> = input.lines().collect();

    let ans1 = part1(&lines);
    println!("Part 1: {}", ans1);

    let ans2 = part2(&lines);
    println!("Part 2: {}", ans2);
}

fn part1(lines: &[&str]) -> i64 {
    let mut num_str: Vec<String> = Vec::new();
    for l in lines {
        num_str.push(l.to_string());
    }
    let mut sum: i64 = 0;
    for s in &num_str {
        sum += get_joltage(s);
    }
    sum
}

fn get_joltage(s: &str) -> i64 {
    let mut num_vec : Vec<i64> = Vec::new();
    for num in s.chars() {
        num_vec.push(num.to_digit(10).unwrap() as i64);
    }
    let highest_index: usize = get_max(&num_vec,0, num_vec.len() - 1);
    let second_highest_index: usize = get_max(&num_vec,highest_index + 1 , num_vec.len());
    let string_joltage = format!("{}{}", num_vec[highest_index], num_vec[second_highest_index]);
    let joltage: i64 = string_joltage.parse().unwrap();
    joltage
}

fn get_max(v: &Vec<i64>, start: usize, end: usize) -> usize {
    assert!(start < end && end <= v.len(), "Invalid range");
    let mut max_index = start;
    for i in start..end {
        if v[i] > v[max_index] {
            max_index = i;
        }
    }
    max_index
}

fn part2(lines: &[&str]) -> i64 {
    let mut num_str: Vec<String> = Vec::new();
    for l in lines {
        num_str.push(l.to_string());
    }
    let mut sum: i64 = 0;
    for s in &num_str {
        sum += largest_number_from_digits(s, 12);
    }
    sum
}


fn largest_number_from_digits(digits: &str, num_digits_to_select: usize) -> i64 {
    let mut selected_digits: Vec<char> = Vec::new();

    let total_digits = digits.len();
    for (index, digit_char) in digits.chars().enumerate() {
        let current_digit = digit_char;
        while !selected_digits.is_empty()
            && *selected_digits.last().unwrap() < current_digit
            && selected_digits.len() + (total_digits - index) > num_digits_to_select
        {
            selected_digits.pop(); 
        }
        if selected_digits.len() < num_digits_to_select {
            selected_digits.push(current_digit);
        }
    }
    let number_string: String = selected_digits.iter().collect();
    let num : i64 = number_string.parse().unwrap();
    num
}

