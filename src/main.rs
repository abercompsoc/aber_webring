mod api;
mod site_indexer;

use std::path::Path;
use actix_web::{self, web, App, HttpServer};
use api::endpoints::*;
use site_indexer::AppState;
use crate::site_indexer::read_file;

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new()
            .route("/invalid_dir", web::get().to(invalid_dir_error))
            .route("/{user_id}", web::get().to(navigate))
            .app_data(web::Data::new(AppState {
                sites: read_file(),
            }))
    })
    .bind(("127.0.0.1", 8080))?
    .run()
    .await
}
