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
    let mut grid: Vec<Vec<char>> = lines
    .iter()
    .map(|s| s.chars().collect())
    .collect();
    let mut total_moves: i64 = 0;
    let rows = grid.len();
    let cols = grid[0].len();
    let directions = [
        (-1, -1), (-1, 0), (-1, 1),
        ( 0, -1),          ( 0, 1),
        ( 1, -1), ( 1, 0), ( 1, 1),
    ];
    let mut to_replace: Vec<(usize, usize)> = Vec::new();
    for i in 0..rows {
        for j in 0..cols {
            if grid[i][j] != '@' {
                continue;
            }
            let mut count = 0;
            for (dx, dy) in directions {
                let ni = i as i32 + dx;
                let nj = j as i32 + dy;
                if ni < 0 || ni >= rows as i32 || nj < 0 || nj >= cols as i32 {
                    count += 1;
                }
                else {
                    let ni = ni as usize;
                    let nj = nj as usize;
                    if grid[ni][nj] == '.' {
                        count += 1;
                    }
                }
            }
            if count > 4 {
                to_replace.push((i, j));
            }
        }
    }
    for (i, j) in to_replace {
        grid[i][j] = 'X';
        total_moves += 1;
    }
    total_moves
}


fn part2(lines: &[&str]) -> i64 {
   let mut grid: Vec<Vec<char>> = lines
        .iter()
        .map(|s| s.chars().collect())
        .collect();
    let mut total_moves: i64 = 0;
    let rows = grid.len();
    let cols = grid[0].len();
    let directions = [
        (-1, -1), (-1, 0), (-1, 1),
        ( 0, -1),          ( 0, 1),
        ( 1, -1), ( 1, 0), ( 1, 1),
    ];
    loop {
        let mut to_replace: Vec<(usize, usize)> = Vec::new();
        for i in 0..rows {
            for j in 0..cols {
                if grid[i][j] != '@' {
                    continue;
                }
                let mut count = 0;
                for (dx, dy) in directions {
                    let ni = i as i32 + dx;
                    let nj = j as i32 + dy;

                    if ni < 0 || ni >= rows as i32 || nj < 0 || nj >= cols as i32 {
                        count += 1;
                    } else {
                        let ni = ni as usize;
                        let nj = nj as usize;
                        if grid[ni][nj] == '.' {
                            count += 1;
                        }
                    }
                }
                if count > 4 {
                    to_replace.push((i, j));
                }
            }
        }
        if to_replace.is_empty() {
            break;
        }
        for (i, j) in &to_replace {
            grid[*i][*j] = 'X';
            total_moves += 1;
        }
        for i in 0..rows {
            for j in 0..cols {
                if grid[i][j] == 'X' {
                    grid[i][j] = '.';
                }
            }
        }
    }
    total_moves
}
