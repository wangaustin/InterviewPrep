export interface GameSummaryDto {
  id: number
  name: string
  genre: string
  price: number
  releaseDate: string
}

export interface GameDetailsDto {
  id: number
  name: string
  genreId: number
  price: number
  releaseDate: string
}

export interface GenreDto {
  id: number
  name: string
}

export interface SaveGameDto {
  name: string
  genreId: number
  price: number
  releaseDate: string
}
