// ========== input all and prepare iterator ==========
fn input() -> std::str::SplitWhitespace {
    let mut s: String = String::new();
    std::io::stdin().read_to_string(&mut s).ok();
    let mut itr = s.trim().split_whitespace();
    itr
}
// ========== write multiple ==========
fn write_all(out: &[u8]) {
    std::io::stdout().write_all(&out).unwrap();
}
// ========== input one element ==========
fn input_one(itr: std::str::SplitWhitespace) -> usize {
    let n: usize = itr.next().unwrap().parse().unwrap();
    n
}
// ========== input array ==========
fn input_array(itr: std::str::SplitWhitespace) -> Vec<usize> {
    let a: Vec<usize> = (0..n)
        .map(|_| itr.next().unwrap().parse().unwrap())
        .collect();
    a
}
// ========== input array2 ==========
fn input_array(itr: std::str::SplitWhitespace) -> Vec<Vec<usize>> {
    let a: Vec<(usize, usize)> = (0..n)
        .map(|_| {
            (
                itr.next().unwrap().parse().unwrap(),
                itr.next().unwrap().parse().unwrap(),
            )
        })
        .collect();
    a
}
// ========== input string ==========
fn input_string(itr: std::str::SplitWhitespace) -> Vec<char> {
    let s: Vec<char> = itr.next().unwrap().chars().collect();
    s
}
// ========== input graph ==========
fn input_graph(n: usize, m: usize, xy: &Vec<(usize, usize)>) -> Vec<Vec<usize>> {
    let mut graph: Vec<Vec<usize>> = vec![Vec::new(); n];
    for i in 0..m {
        graph[xy[i].0].push(xy[i].1);
        graph[xy[i].1].push(xy[i].0);
    }
    graph
}
// ========== input grid ==========
fn input_grid(h: usize, w: usize) -> Vec<Vec<char>> {
    let h: usize = itr.next().unwrap().parse().unwrap();
    let w: usize = itr.next().unwrap().parse().unwrap();
    let grid: Vec<Vec<char>> = (0..h)
        .map(|_| itr.next().unwrap().chars().collect())
        .collect();
    grid
}

// ========== input string to digit ==========
fn input_string_as_digit(s: String) -> Vec<u64> {
    let s: Vec<u64> = s
        .trim()
        .chars()
        .map(|c| c.to_digit(10).unwrap() as u64)
        .collect();
    s
}
