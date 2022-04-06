<template>
  <div class="panel">
    <Color v-if="index == 1" />
    <System v-if="index == 2" />
    <MusicReaction v-if="index == 3" />
    <PatternMode v-if="index == 4" />
    <SettingBox v-if="index == 5" />

    <el-button v-if="index != 2" class="save-button">SAVE</el-button>
  </div>
</template>

<script>
import Color from "./Color";
import System from "./System";
import MusicReaction from "./MusicReaction";
import PatternMode from "./PatternMode";
import SettingBox from "./SettingBox";
export default {
  props: {
    index: String,
  },
  data() {
    return {
      selectedTab: null,
    };
  },
  components: {
    Color,
    System,
    MusicReaction,
    PatternMode,
    SettingBox,
  },
  mounted: function () {},
};
</script>
<style>
.el-button.save-button {
  font-weight: 700;
  height: 38px;
  
  background: #351c75;
  color: #ff3399;
  position: absolute;
  bottom: 1px;
  left: 1px;
  width: calc(100vw - 2px);
}
</style>