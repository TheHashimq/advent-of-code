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

fn parse_input(lines: &[&str]) -> (Vec<(i64, i64)>, Vec<i64>) {
    let mut ranges: Vec<(i64, i64)> = Vec::new();
    let mut values: Vec<i64> = Vec::new();
    let mut reading_ranges = true;
    for &line in lines {
        if line.trim().is_empty() {
            reading_ranges = false;
            continue;
        }
        if reading_ranges {
            let parts: Vec<&str> = line.split('-').collect();
            let start: i64 = parts[0].parse().unwrap();
            let end: i64 = parts[1].parse().unwrap();
            ranges.push((start, end));
        } else {
            values.push(line.parse::<i64>().unwrap());
        }
    }
    (ranges, values)
}

fn part1(lines: &[&str]) -> i64 {
    let (ranges, values) = parse_input(lines);
    let mut fresh_id: i64 = 0;
    for v in &values {
        let mut found_in_any_range = false;
        for (start, end) in &ranges {
            if *v >= *start && *v <= *end {
                found_in_any_range = true;
                break;
            }
        }
        if found_in_any_range {
            fresh_id += 1;
        }
    }
    fresh_id
}

fn merge_ranges(ranges: &[ (i64, i64) ]) -> Vec<(i64, i64)> {
    if ranges.is_empty() {
        return vec![];
    }
    let mut sorted_ranges = ranges.to_vec();
    sorted_ranges.sort_by(|a, b| a.0.cmp(&b.0).then(a.1.cmp(&b.1)));
    let mut merged: Vec<(i64, i64)> = Vec::new();
    let mut current = sorted_ranges[0];
    for &range in sorted_ranges.iter().skip(1) {
        let (start, end) = range;
        if start <= current.1 {
            current.1 = current.1.max(end);
        } else {
            merged.push(current);
            current = range;
        }
    }
    merged.push(current);
    merged
}

fn part2(lines: &[&str]) -> i64 {
    let (ranges, _) = parse_input(lines);
    let merged_ranges = merge_ranges(&ranges);
    let mut total_fresh_id_number: i64 = 0;
    for (start, end) in &merged_ranges {
        total_fresh_id_number += end - start + 1;
    }
    total_fresh_id_number
}

