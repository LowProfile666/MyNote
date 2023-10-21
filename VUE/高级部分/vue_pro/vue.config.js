const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  // 保存时是否进行语法检查。true表示检查，false表示不检查。默认值是true。
  lintOnSave : false,
  // 配置入口
  pages: {
    index: {
      entry: 'src/main.js',
    }
  },
  
  /* devServer : {
    proxy : "http://localhost:8000"
  } */

  devServer: {
    proxy: {
      '/api': {
        target: 'http://localhost:8000',
        pathRewrite: {'^/api' : ''},
        ws: true,
        changeOrigin: true
      },
	  '/abc': {
        target: 'http://localhost:8001',
        pathRewrite: {'^/abc' : ''},
        ws: true,
        changeOrigin: true
      }
    }
  }

})
