<script setup lang="ts">
import { computed, onMounted, ref } from 'vue'
import { useRoute, useRouter } from 'vue-router'

import { gamesApi } from '../../api/gamesApi'
import { genresApi } from '../../api/genresApi'
import type { GameDetailsDto, GenreDto, SaveGameDto } from '../../api/types'
import { useUiStore } from '../../shared/stores/uiStore'
import GameForm from './GameForm.vue'

const game = ref<GameDetailsDto | null>(null)
const genres = ref<GenreDto[]>([])
const isLoading = ref(false)
const isSubmitting = ref(false)
const error = ref('')

const route = useRoute()
const router = useRouter()
const uiStore = useUiStore()

const gameId = computed(() => Number(route.params.id))

const initialValue = computed<SaveGameDto | undefined>(() => {
  if (!game.value) {
    return undefined
  }

  return {
    name: game.value.name,
    genreId: game.value.genreId,
    price: game.value.price,
    releaseDate: game.value.releaseDate
  }
})

async function loadData() {
  if (Number.isNaN(gameId.value)) {
    error.value = 'Invalid game id.'
    return
  }

  isLoading.value = true
  error.value = ''

  try {
    const [gameResult, genresResult] = await Promise.all([
      gamesApi.getById(gameId.value),
      genresApi.getAll()
    ])

    game.value = gameResult
    genres.value = genresResult
  } catch {
    error.value = 'Could not load game details.'
  } finally {
    isLoading.value = false
  }
}

async function updateGame(payload: SaveGameDto) {
  isSubmitting.value = true
  error.value = ''

  try {
    await gamesApi.update(gameId.value, payload)
    uiStore.showMessage('Game updated.')
    await router.push('/')
  } catch {
    error.value = 'Could not update game.'
  } finally {
    isSubmitting.value = false
  }
}

async function deleteGame() {
  isSubmitting.value = true
  error.value = ''

  try {
    await gamesApi.remove(gameId.value)
    uiStore.showMessage('Game deleted.')
    await router.push('/')
  } catch {
    error.value = 'Could not delete game.'
  } finally {
    isSubmitting.value = false
  }
}

onMounted(loadData)
</script>

<template>
  <section>
    <div class="section-title">
      <h2>Edit Game</h2>
      <button class="danger" :disabled="isSubmitting" @click="deleteGame">Delete</button>
    </div>

    <p v-if="isLoading">Loading game...</p>
    <p v-else-if="error" class="error">{{ error }}</p>
    <GameForm
      v-else-if="initialValue"
      :genres="genres"
      :initial-value="initialValue"
      submit-text="Save Changes"
      :disabled="isSubmitting"
      @save="updateGame"
    />
  </section>
</template>
