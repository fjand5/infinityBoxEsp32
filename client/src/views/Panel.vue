<template>
  <div class="panel">
    <Color v-if="index == 1" />
    <System v-if="index == 2" />
    <MusicReaction v-if="index == 3" />
    <PatternMode v-if="index == 4" />
    <SettingBox v-if="index == 5" />

    <el-button class="save-button">SAVE</el-button>
  </div>
</template>

<script>
import Color from "./Color";
import System from "./System";
import MusicReaction from "./MusicReaction";
import PatternMode from "./PatternMode";
import SettingBox from "./SettingBox";
// import EspSwitch from "../components/EspSwitch";
// import EspSlider from "../components/EspSlider";
// import EspInput from "../components/EspInput";
// import EspColorPicker from "../components/EspColorPicker";
// import EspSelect from "../components/EspSelect";
// import { mapGetters } from "vuex";
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
    // EspButton,
    // EspSwitch,
    // EspSlider,
    // EspInput,
    // EspColorPicker,
    // EspSelect
  },
  mounted: function () {},
};
</script>
<style>
/* .kc_fab_main_btn{
  position: absolute;
  right: 22px;
  bottom: 22px;
  background-color: #ff3399;
  color: #351c75;
  width: 60px;
  height: 60px;
  border-radius: 100%;
  font-size: 32px;
  box-shadow:  0 3px 6px rgba(0,0,0,0.2), 0 3px 6px rgba(0,0,0,0.23);
}
.kc_fab_main_btn i {
 position: relative;
 left: -6px;
} */
.el-button.save-button {
  font-weight: 500;
  height: 32px;
  
  background: #351c75;
  color: #ff3399;
  position: absolute;
  bottom: 15px;
  left: 1px;
  width: calc(100vw - 2px);
}
</style>