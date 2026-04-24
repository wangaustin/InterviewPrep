<script setup lang="ts">
import { RouterView } from 'vue-router'
import { storeToRefs } from 'pinia'

import { useUiStore } from './shared/stores/uiStore'

const uiStore = useUiStore()
const { flashMessage } = storeToRefs(uiStore)
</script>

<template>
  <div class="page">
    <header class="topbar">
      <div>
        <p class="eyebrow">Admin Console</p>
        <h1>GameStore</h1>
      </div>
      <nav>
        <RouterLink to="/">Games</RouterLink>
        <RouterLink to="/games/new">Add Game</RouterLink>
      </nav>
    </header>

    <main>
      <p v-if="flashMessage" class="flash">{{ flashMessage }}</p>
      <RouterView />
    </main>
  </div>
</template>
