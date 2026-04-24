import { apiClient } from './client'
import type { GameDetailsDto, GameSummaryDto, SaveGameDto } from './types'

export const gamesApi = {
  async getAll(): Promise<GameSummaryDto[]> {
    const response = await apiClient.get<GameSummaryDto[]>('/games')
    return response.data
  },

  async getById(id: number): Promise<GameDetailsDto> {
    const response = await apiClient.get<GameDetailsDto>(`/games/${id}`)
    return response.data
  },

  async create(payload: SaveGameDto): Promise<GameDetailsDto> {
    const response = await apiClient.post<GameDetailsDto>('/games', payload)
    return response.data
  },

  async update(id: number, payload: SaveGameDto): Promise<void> {
    await apiClient.put(`/games/${id}`, payload)
  },

  async remove(id: number): Promise<void> {
    await apiClient.delete(`/games/${id}`)
  }
}
