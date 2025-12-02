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

    let mut s = String::from("");
    for l in lines {
        s.push_str(l);
    }
    let parts: Vec<&str> = s.split(',').collect();
    let mut valid_id : Vec<i64> = Vec::new();
    for p in parts {
        let mut iter = p.split('-').map(|x| x.parse::<i64>().unwrap());
        let start = iter.next().unwrap();
        let end = iter.next().unwrap();
        for id in start..=end {
            if is_valid_id(id){
                valid_id.push(id);
            }
        }
    }

    let mut sum: i64 = 0;
    for num in valid_id {
        sum += num;
    }
    sum
}

fn is_valid_id(id: i64) -> bool {
    let s = id.to_string();
    if s.len() % 2 != 0 {
        return false;
    }
    let mid = s.len() / 2;
    let (first, second) = s.split_at(mid);
    first == second
}

fn part2(lines: &[&str]) -> i64 {
    let mut s = String::from("");
    for l in lines {
        s.push_str(l);
    }
    let parts: Vec<&str> = s.split(',').collect();
    let mut valid_id : Vec<i64> = Vec::new();
    for p in parts {
        let mut iter = p.split('-').map(|x| x.parse::<i64>().unwrap());
        let start = iter.next().unwrap();
        let end = iter.next().unwrap();
        for id in start..=end {
            if is_repeating(id){
                valid_id.push(id);
            }
        }
    }

    let mut sum: i64 = 0;
    for num in valid_id {
        sum += num;
    }
    sum
}

// Knutt Morris Pratt Algorithm
// 
fn is_repeating(id: i64) -> bool {
    let s = id.to_string();
    let n = s.len();
    if n <= 1 {
        return false; 
    }

    // Build prefix function
    let mut pi = vec![0; n];
    let mut j = 0;

    for i in 1..n {
        while j > 0 && s.as_bytes()[i] != s.as_bytes()[j] {
            j = pi[j - 1];
        }
        if s.as_bytes()[i] == s.as_bytes()[j] {
            j += 1;
        }
        pi[i] = j;
    }

    // Length of smallest repeating unit
    let p = n - pi[n - 1];

    // Check if repeating
    p != n && n % p == 0
}
