import axios from 'axios'

const defaultBaseUrl = 'http://localhost:5026'

export const apiClient = axios.create({
  baseURL: import.meta.env.VITE_API_BASE_URL ?? defaultBaseUrl,
  headers: {
    'Content-Type': 'application/json'
  }
})
