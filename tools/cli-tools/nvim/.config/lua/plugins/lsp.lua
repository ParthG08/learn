return {
  "neovim/nvim-lspconfig",
  lazy = false,
  dependencies = {
    "williamboman/mason.nvim",
  },
  config = function()
    -- 1. Initialize Mason so 'jdtls' is available on your system
    require("mason").setup()

    -- 2. Safely load lspconfig JUST to register the :LspInfo command
    pcall(require, "lspconfig")

    -- 3. Use pure Neovim 0.11 native API to start Java (Bypasses all plugin bugs)
    vim.api.nvim_create_autocmd("FileType", {
      pattern = "java",
      callback = function()
        vim.lsp.start({
          name = "jdtls",
          cmd = { "jdtls" },
          -- This tells Neovim where the root of your Khatabook/Java project is
          root_dir = vim.fs.root(0, { ".git", "pom.xml", "build.gradle", "mvnw" }),
        })
      end,
    })
  end,
}


