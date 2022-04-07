<template>
  <el-container>
    <el-header height="75" style="padding: 0">
      <el-menu
        mode="horizontal"
        @select="handleSelect"
        background-color="#351c75"
        text-color="#ff3399"
      >
        <el-menu-item index="1">COLOR</el-menu-item>
        <el-menu-item index="2" style="border-right: 1px solid white"
          >SYSTEM</el-menu-item
        >
        <el-menu-item index="3">MUSIC REACTION</el-menu-item>
        <el-menu-item index="4" style="border-right: 1px solid white"
          >PATTERN</el-menu-item
        >
        <el-menu-item index="5"  style="width: 100%; border-right: 1px solid white" >SETTING BOX</el-menu-item>
      </el-menu>
    </el-header>
    <el-main>
      <Panel :index="index" />
    </el-main>
  </el-container>
</template>
<script>
import Panel from "./Panel";

export default {
  data() {
    return {
      index: "1",
    };
  },
  components: { Panel },
  mounted: function () {
        this.$store.dispatch("initCommand")

  },
  methods: {
    handleSelect: function (index) {
      this.index = index;
    },
  },
};
</script>

<style scoped>
.el-main {
  padding: 22px 2px;
  max-height: 100vh;
}
.el-menu {
   background-color: #ffffff !important;
}
.el-menu--horizontal > .el-menu-item {
  width: 50%;
  font-weight: 500;
  border-left: 1px solid white;
  border-top: 1px solid white;
  border-bottom: 1px solid white;

  height: 35px;
  border-radius: 5px;

  line-height: 35px;
}
.is-active {
  color: #351c75;
  background-color: #ff3399 !important;
  font-weight: 1000;
  /* border-bottom: 0px solid #ff3399 !important; */
}
</style>