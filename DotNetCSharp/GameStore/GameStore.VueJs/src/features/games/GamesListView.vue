<script setup lang="ts">
import { onMounted, ref } from 'vue'

import { gamesApi } from '../../api/gamesApi'
import type { GameSummaryDto } from '../../api/types'
import { formatCurrency, formatDate } from '../../shared/utils/formatters'

const games = ref<GameSummaryDto[]>([])
const isLoading = ref(false)
const error = ref('')

async function loadGames() {
  isLoading.value = true
  error.value = ''

  try {
    games.value = await gamesApi.getAll()
  } catch {
    error.value = 'Could not load games.'
  } finally {
    isLoading.value = false
  }
}

onMounted(loadGames)
</script>

<template>
  <section>
    <div class="section-title">
      <h2>Games</h2>
      <RouterLink class="button-link" to="/games/new">Add Game</RouterLink>
    </div>

    <p v-if="isLoading">Loading games...</p>
    <p v-else-if="error" class="error">{{ error }}</p>

    <p v-else-if="games.length === 0">No games found. Add your first one.</p>

    <table v-else>
      <thead>
        <tr>
          <th>Name</th>
          <th>Genre</th>
          <th>Price</th>
          <th>Release Date</th>
          <th></th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="game in games" :key="game.id">
          <td data-label="Name">{{ game.name }}</td>
          <td data-label="Genre">{{ game.genre }}</td>
          <td data-label="Price">{{ formatCurrency(game.price) }}</td>
          <td data-label="Release">{{ formatDate(game.releaseDate) }}</td>
          <td data-label="Action">
            <RouterLink :to="`/games/${game.id}/edit`">Edit</RouterLink>
          </td>
        </tr>
      </tbody>
    </table>
  </section>
</template>
