// ========== z-algorithm ==========
fn z_algorithm(s: String) -> Vec<usize> {
    let s: Vec<char> = s.chars().collect();
    let n = s.len();
    let mut a: Vec<usize> = vec![0; s.len()];
    a[0] = n;
    let mut i = 1;
    let mut j = 0;
    while i < n {
        while i + j < n && s[j] == s[i + j] {
            j += 1;
        }
        a[i] = j;
        if j == 0 {
            i += 1;
            continue;
        }
        let mut k = 1;
        while i + k < n && k + a[k] < j {
            a[i + k] = a[k];
            k += 1;
        }
        i += k;
        j -= k;
    }
    a
}
