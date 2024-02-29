use std::{fs, path::Path};

pub struct AppState {
    pub sites: Vec<(String, String)>,
}

pub fn read_file() -> Vec<(String, String)> {
    let path_string = std::env::args().nth(1).expect("no path given");
    let path = Path::new(&path_string);
    
    let data = fs::read_to_string(path).expect("Unable to read file");
    let site_info = data
        .lines()
        .filter(|line| line.split_once(" ").is_some())
        .map(|line| {
            let info = line.split_once(" ").unwrap();
            (info.0.to_string(), info.1.to_string())
        })
        .collect::<Vec<_>>();
    
    site_info
}
