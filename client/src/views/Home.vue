<template>
  <el-container>
    <el-main v-loading="getSending">
      <Panel v-if="getAuthStatus || !getManifest.auth" />
    </el-main>
    <el-footer>
      <div v-if="getManifest.creator">
      {{getManifest.creator}}
      </div>
      <div v-else>Email: huynhtheluat@gmail.com</div>
      </el-footer>
  </el-container>
</template>

<script>
import { mapGetters } from "vuex";
import Panel from "./Panel.vue";
export default {
  data() {
    return {
      activeIndex: "1",
      activeIndex2: "1",
    };
  },
  components: {
    Panel,
  },
  computed: {
    ...mapGetters([
      "getAuthStatus",
      "getCurrentWifi",
      "getSending",
      "getResponseTime",
      "getUptime",
      "getManifest",
    ]),
  },
  mounted: function () {
    this.$store.dispatch("requireManifestData").then(() => {
      if (this.getManifest.auth) this.$showLogin()
    });
  },
  methods: {
    showWifi: function () {
      if (this.getManifest.wifiSta) {
        this.$showWifiSelector()
      }
    },
  },
};
</script>

<style scoped>
.el-header {
  background: #545c64;
}
.wifi-button {
  display: flex;
  justify-content: end;
  align-items: center;
}
.cell {
  cursor: pointer;
}
</style>