return {
  'lewis6991/gitsigns.nvim',
  config = function()
    require('gitsigns').setup({
      current_line_blame = true,
      on_attach = function(bufnr)
        local gs = package.loaded.gitsigns
        vim.keymap.set('n', '<leader>gp', gs.preview_hunk, {buffer = bufnr, desc = "Preview Git Hunk"})
      end
    })
  end
}
