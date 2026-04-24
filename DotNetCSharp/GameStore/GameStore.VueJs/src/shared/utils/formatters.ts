const currencyFormatter = new Intl.NumberFormat('en-US', {
  style: 'currency',
  currency: 'USD'
})

export function formatCurrency(value: number): string {
  return currencyFormatter.format(value)
}

export function formatDate(value: string): string {
  if (!value) {
    return ''
  }

  const date = new Date(`${value}T00:00:00`)
  return date.toLocaleDateString('en-US', {
    year: 'numeric',
    month: 'short',
    day: 'numeric'
  })
}
