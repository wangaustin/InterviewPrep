# GameStore Vue Frontend

Vue 3 + TypeScript frontend for the GameStore API.

## Prerequisites

- Node.js 20+
- .NET API running from `GameStore.Api`

## Configure

Copy `.env.example` to `.env` and update if needed:

```bash
cp .env.example .env
```

Default API URL:

```text
http://localhost:5026
```

## Run

```bash
npm install
npm run dev
```

The Vite dev server runs at `http://localhost:5173`.

## Build

```bash
npm run build
```

## App Routes

- `/` list games
- `/games/new` create a game
- `/games/:id/edit` edit or delete a game
