<template>
  <div id="app">
    <img class="logo-bg" src="/static/logo.png" />

    <Home />
  </div>
</template>

<script>
import Home from "./views/Home.vue";

export default {
  name: "App",
  components: {
    Home,
  },
};
</script>

<style>
.logo-bg {
  position: absolute;
  margin-left: auto;
  margin-right: auto;
  top: 320px;
  left: 0;
  right: 0;
  width: 90%;
}
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  height: 100vh;
  /* background: hsl(330, 50%, 80%); */
  
  background: linear-gradient(to top,hsl(257, 20%, 20%) , hsl(330, 20%, 90%) ) ;
}
body {
  margin: 0;
}
</style>
