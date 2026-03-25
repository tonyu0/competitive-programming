// ========== compress array ==========
fn compress_array(a: &Vec<T>) -> std::collections::HashMap {
    let mut b = a.clone();
    b.sort();
    b.dedup();
    let mut c = std::collections::HashMap::new();
    for i in 0..b.len() {
        c.insert(b[i], i);
    }
    c
}
// ========== lower_bound ==========
fn lower_bound<T: PartialOrd>(x: T, a: &Vec<T>) -> usize {
    let mut l: usize = 0;
    let mut r: usize = a.len();
    while r != l {
        let mid = (l + r) >> 1;
        if a[mid] < x {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    l
}
// ========== upper_bound ==========
fn upper_bound<T: PartialOrd>(x: T, a: &Vec<T>) -> usize {
    let mut l: usize = 0;
    let mut r: usize = a.len();
    while r != l {
        let mid = (l + r) >> 1;
        if a[mid] > x {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    l
}

// ========== move on grid ==========
fn move_on_grid() {
    let dx: Vec<isize> = [0, -1, 0, 1, -1, 1, -1, 1].to_vec();
    let dy: Vec<isize> = [1, 0, -1, 0, -1, 1, 1, -1].to_vec();
    for y in 0..h {
        for x in 0..w {
            for i in 0..8 {
                let nx = x as isize + dx[i];
                let ny = y as isize + dy[i];
                if 0 <= nx && nx < w as isize && 0 <= ny && ny < h as isize {
                    // do something on grid
                }
            }
        }
    }
}
