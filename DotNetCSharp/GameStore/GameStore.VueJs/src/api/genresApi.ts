import { apiClient } from './client'
import type { GenreDto } from './types'

export const genresApi = {
  async getAll(): Promise<GenreDto[]> {
    const response = await apiClient.get<GenreDto[]>('/genres')
    return response.data
  }
}
