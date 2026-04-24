import { createRouter, createWebHistory } from 'vue-router'

import { GameCreateView } from '../features/games/GameCreateView'
import { GameEditView } from '../features/games/GameEditView'
import { GamesListView } from '../features/games/GamesListView'

export const router = createRouter({
  history: createWebHistory(),
  routes: [
    { path: '/', component: GamesListView },
    { path: '/games/new', component: GameCreateView },
    { path: '/games/:id/edit', component: GameEditView, props: true }
  ]
})
