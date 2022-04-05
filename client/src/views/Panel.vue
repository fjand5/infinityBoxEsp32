<template>
  <div class="panel">
    <Color
    v-if="index == 1"
    />
    <System
    v-if="index == 2"
    />
    <MusicReaction
    v-if="index == 3"
    />
    <PatternMode
    v-if="index == 4"
    />
    <SettingBox
    v-if="index == 5"
    />
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
  props:{
    index: String
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
    SettingBox
    // EspButton,
    // EspSwitch,
    // EspSlider,
    // EspInput,
    // EspColorPicker,
    // EspSelect
  },
  mounted: function () {
 
  },
 
};
</script>
<style scoped>
</style>