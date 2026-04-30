# GameStore

Full-stack GameStore app with:

- `GameStore.Api`: ASP.NET Core Minimal API + EF Core + SQLite
- `GameStore.VueJs`: Vue 3 + TypeScript + Vite frontend

## Tech Stack

- .NET `10.0`
- ASP.NET Core Minimal APIs
- Entity Framework Core (`Microsoft.EntityFrameworkCore.Sqlite`)
- SQLite (`GameStore.db`)
- Vue 3 + TypeScript
- Vue Router + Pinia + Axios

## Project Structure

```text
GameStore/
├── GameStore.Api/      # Backend API
├── GameStore.VueJs/    # Frontend app
├── GameStore.sln
└── GameStore.slnx
```

## Prerequisites

- .NET SDK `10.0`
- Node.js `20+`
- npm

## Quick Start

Run backend and frontend in separate terminals.

### 1) Start API

```bash
cd DotNetCSharp/GameStore/GameStore.Api
dotnet run
```

Default API URL:

- `http://localhost:5026`

Notes:

- CORS allows the Vite dev origin: `http://localhost:5173`
- Database migrations are applied automatically on startup
- Initial genre seed data is inserted if the `Genres` table is empty

### 2) Start Frontend

```bash
cd DotNetCSharp/GameStore/GameStore.VueJs
cp .env.example .env
npm install
npm run dev
```

Default frontend URL:

- `http://localhost:5173`

## Environment Configuration

Frontend API base URL is read from:

- `VITE_API_BASE_URL`

If not set, it defaults to:

- `http://localhost:5026`

## API Endpoints

Base URL: `http://localhost:5026`

### Games

- `GET /games/` - List games
- `GET /games/{id}` - Get game by id
- `POST /games/` - Create game
- `PUT /games/{id}` - Update game
- `DELETE /games/{id}` - Delete game

Create/Update payload:

```json
{
  "name": "Street Fighter II",
  "genreId": 1,
  "price": 39.99,
  "releaseDate": "1991-02-06"
}
```

Validation:

- `name`: required, max 50 chars
- `genreId`: 1-50
- `price`: 1-100
- `releaseDate`: `YYYY-MM-DD`

### Genres

- `GET /genres/` - List genres

## Frontend Routes

- `/` - Games list
- `/games/new` - Create game
- `/games/:id/edit` - Edit/Delete game

## Useful Commands

### Backend

```bash
cd DotNetCSharp/GameStore/GameStore.Api
dotnet build
dotnet run
```

### Frontend

```bash
cd DotNetCSharp/GameStore/GameStore.VueJs
npm run dev
npm run build
npm run preview
```
