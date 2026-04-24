<script setup lang="ts">
import { computed, reactive, watch } from 'vue'

import type { GenreDto, SaveGameDto } from '../../api/types'

const props = defineProps<{
  genres: GenreDto[]
  initialValue?: SaveGameDto
  submitText: string
  disabled?: boolean
}>()

const emit = defineEmits<{
  save: [value: SaveGameDto]
}>()

const form = reactive<SaveGameDto>({
  name: props.initialValue?.name ?? '',
  genreId: props.initialValue?.genreId ?? 0,
  price: props.initialValue?.price ?? 0,
  releaseDate: props.initialValue?.releaseDate ?? ''
})

watch(
  () => props.initialValue,
  (value) => {
    if (!value) {
      return
    }

    form.name = value.name
    form.genreId = value.genreId
    form.price = value.price
    form.releaseDate = value.releaseDate
  },
  { immediate: true }
)

const isValid = computed(
  () =>
    form.name.trim().length > 0 &&
    form.genreId > 0 &&
    form.price >= 1 &&
    form.price <= 100 &&
    form.releaseDate.length > 0
)

function onSubmit() {
  emit('save', {
    name: form.name.trim(),
    genreId: Number(form.genreId),
    price: Number(form.price),
    releaseDate: form.releaseDate
  })
}
</script>

<template>
  <form class="game-form" @submit.prevent="onSubmit">
    <label>
      Name
      <input v-model="form.name" type="text" maxlength="50" required />
    </label>

    <label>
      Genre
      <select v-model.number="form.genreId" required>
        <option :value="0" disabled>Select a genre</option>
        <option v-for="genre in genres" :key="genre.id" :value="genre.id">{{ genre.name }}</option>
      </select>
    </label>

    <label>
      Price
      <input v-model.number="form.price" type="number" min="1" max="100" step="0.01" required />
    </label>

    <label>
      Release Date
      <input v-model="form.releaseDate" type="date" required />
    </label>

    <button :disabled="!isValid || disabled" type="submit">{{ submitText }}</button>
  </form>
</template>
