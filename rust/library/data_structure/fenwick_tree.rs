// ========== BinaryIndexedTree ==========
mod fenwick_tree {
    use std::ops::*;
    pub struct FenwickTree<T> {
        size: usize,
        data: Vec<T>,
        identity: T,
    }
    impl<T: Copy + Clone + AddAssign + Sub<Output = T>> FenwickTree<T> {
        pub fn new(size: usize, id: T) -> FenwickTree<T> {
            FenwickTree {
                size: size,
                data: vec![id; size + 2],
                identity: id,
            }
        }
        pub fn query(&self, i: usize) -> T {
            let mut res = self.identity;
            let mut idx = i as isize - 1;
            while idx >= 0 {
                res += self.data[idx as usize];
                idx = (idx & (idx + 1)) - 1;
            }
            res
        }
        pub fn update(&mut self, i: usize, x: T) {
            let mut idx = i;
            while idx <= self.size {
                self.data[idx] += x;
                idx |= idx + 1;
            }
        }
    }
}

// ========== fenwick(1-indexed) ==========
mod fenwick_tree {
    use std::ops::*;
    pub struct FenwickTree<T, F> {
        data: Vec<T>,
        identity: T,
        operation: F,
    }
    impl<T: Copy + Clone, F: Fn(T, T) -> T> FenwickTree<T, F> {
        pub fn new(size: usize, id: T, op: F) -> FenwickTree<T, F> {
            FenwickTree {
                data: vec![id; size + 1],
                identity: id,
                operation: op,
            }
        }
        pub fn query(&self, i: usize) -> T {
            let mut res = self.identity;
            let mut idx = i as isize - 1;
            while idx >= 0 {
                res = (self.operation)(res, self.data[idx as usize]);
                idx = (idx & (idx + 1)) - 1;
            }
            res
        }
        pub fn update(&mut self, i: usize, x: T) {
            let mut idx = i;
            while idx < self.data.len() {
                self.data[idx] = (self.operation)(self.data[idx], x);
                idx |= idx + 1;
            }
        }
    }
}
