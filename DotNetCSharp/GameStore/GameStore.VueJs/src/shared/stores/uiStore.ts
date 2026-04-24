import { defineStore } from 'pinia'
import { ref } from 'vue'

export const useUiStore = defineStore('ui-store', () => {
  const flashMessage = ref('')

  function showMessage(message: string) {
    flashMessage.value = message
    window.setTimeout(() => {
      flashMessage.value = ''
    }, 3000)
  }

  return {
    flashMessage,
    showMessage
  }
})
