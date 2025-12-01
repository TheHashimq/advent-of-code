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
    let mut zero_count: i64 = 0;
    let mut current :i64 = 50;
    for l in lines {
        let num: i64 = l[1..].parse().unwrap();
        match l.chars().nth(0).unwrap(){
            'R' => {current = (current + num) % 100;}
            'L' => {current = (current - num) % 100;}
            _ => {println!("error");}
        }
        if current == 0 { zero_count+=1 }
    }
    zero_count
}

fn part2(lines: &[&str]) -> i64 {
    let mut zero_count: i64 = 0;
    let mut current: i64 = 50;
    for l in lines {
        let dir = l.chars().next().unwrap();
        let num: i64 = l[1..].parse().unwrap();
        match dir {
            'R' => {
                zero_count += (current + num) / 100;
                current = (current + num) % 100;
            }
            'L' => {
                let distance_to_zero = if current == 0 { 100 } else { current };
                if num >= distance_to_zero {
                    zero_count += 1 + (num - distance_to_zero) / 100;
                }
                current = ((current - num) % 100 + 100) % 100;
            }
            _ => {}
        }
    }
    zero_count
}
