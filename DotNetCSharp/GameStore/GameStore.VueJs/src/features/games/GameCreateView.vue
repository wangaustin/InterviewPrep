<script setup lang="ts">
import { onMounted, ref } from 'vue'
import { useRouter } from 'vue-router'

import { gamesApi } from '../../api/gamesApi'
import { genresApi } from '../../api/genresApi'
import type { GenreDto, SaveGameDto } from '../../api/types'
import { useUiStore } from '../../shared/stores/uiStore'
import GameForm from './GameForm.vue'

const genres = ref<GenreDto[]>([])
const isSubmitting = ref(false)
const isLoading = ref(false)
const error = ref('')

const router = useRouter()
const uiStore = useUiStore()

async function loadGenres() {
  isLoading.value = true
  error.value = ''

  try {
    genres.value = await genresApi.getAll()
  } catch {
    error.value = 'Could not load genres.'
  } finally {
    isLoading.value = false
  }
}

async function createGame(payload: SaveGameDto) {
  isSubmitting.value = true
  error.value = ''

  try {
    await gamesApi.create(payload)
    uiStore.showMessage('Game created.')
    await router.push('/')
  } catch {
    error.value = 'Could not create game.'
  } finally {
    isSubmitting.value = false
  }
}

onMounted(loadGenres)
</script>

<template>
  <section>
    <h2>Add Game</h2>
    <p v-if="isLoading">Loading genres...</p>
    <p v-else-if="error" class="error">{{ error }}</p>
    <GameForm
      v-else
      :genres="genres"
      submit-text="Create Game"
      :disabled="isSubmitting"
      @save="createGame"
    />
  </section>
</template>
