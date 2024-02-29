use std::ops::Index;
use actix_web::{web, HttpRequest, HttpResponse, Responder};
use serde::Deserialize;
use crate::site_indexer::AppState;

#[derive(Debug, Deserialize)]
pub struct Params {
    dir: String,
}

pub async fn navigate(req: HttpRequest, path: web::Path<String>, data: web::Data<AppState>) -> impl Responder {
    let user_id = path.into_inner();
    let sites = &data.sites;

    let current_index = sites.iter().position(|s| s.0 == user_id).unwrap();

    if let Ok(params) = web::Query::<Params>::from_query(req.query_string()) {
        let direction: isize = match params.dir.as_str() {
            "left" => -1,
            "right" => 1,
            _ => 0
        };

        web::Redirect::to(sites[(current_index as isize + direction) as usize].1.clone())
    } else {
        web::Redirect::to("/invalid_dir")
    }
}

pub async fn invalid_dir_error(req: HttpRequest) -> impl Responder {
    HttpResponse::Ok().body("<h1>An invalid direction was given to the server</h1><h2>Contact the author of the website you just came from and let them know :)</h2>")
}
