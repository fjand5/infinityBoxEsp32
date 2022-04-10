<template>
  <div class="system">
    <el-row :gutter="5">
      <el-col :span="24">
        <el-input placeholder="Router Wifi" v-model="sta_id">
          <template slot="prepend">Wifi</template>
          <template slot="append">
            <el-button  @click="setStaId"> OK </el-button>
          </template>
        </el-input>
      </el-col>
      <el-col :span="24">
        <el-input
          :show-password="true"
          placeholder="Router Password"
          v-model="sta_pass"
        >
          <template slot="prepend">Password</template>
          <template slot="append">
            <el-button  @click="setStaPass"> OK </el-button>
          </template>
        </el-input>
      </el-col>
    </el-row>
    
    <el-row :gutter="5">
      <el-col :span="24">
        <el-input placeholder="Access Point" v-model="ap_id">
          <template slot="prepend">Wifi AP</template>
          <template slot="append">
            <el-button  @click="setApId"> OK </el-button>
          </template>
        </el-input>
      </el-col>
      <el-col :span="24">
        <el-input
          :show-password="true"
          placeholder="Access Point Password"
          v-model="ap_pass"
        >
          <template slot="prepend">Password</template>
          <template slot="append">
            <el-button @click="setApPass"> OK </el-button>
          </template>
        </el-input>
      </el-col>
    </el-row>
  </div>
</template>

<script>
import { mapGetters } from "vuex";

export default {
  data: function () {
    return {
      sta_id: "",
      sta_pass: "",
      ap_id: "",
      ap_pass: "",
    };
  },
  computed: {
    ...mapGetters(["getData"]),
  },
  mounted:function(){
      this.sta_id = this.getData.sta_id;
      this.sta_pass = this.getData.sta_pass;
      this.ap_id = this.getData.ap_id;
      this.ap_pass = this.getData.ap_pass;
  },
  methods: {
    setStaId: function () {
      this.$store.dispatch("sendCommand", {
        espKey: "sta_id",
        espValue: this.sta_id,
      });
    },
    setStaPass: function () {
      this.$store.dispatch("sendCommand", {
        espKey: "sta_pass",
        espValue: this.sta_pass,
      });
    },
    setApId: function () {
      this.$store.dispatch("sendCommand", {
        espKey: "ap_id",
        espValue: this.ap_id,
      });
    },
    setApPass: function () {
      this.$store.dispatch("sendCommand", {
        espKey: "ap_pass",
        espValue: this.ap_pass,
      });
    },
  },
  watch: {
    // getData: function (n) {
    //   this.sta_id = n.sta_id;
    //   this.sta_pass = n.sta_pass;
    //   this.ap_id = n.ap_id;
    //   this.ap_pass = n.ap_pass;
    // },
  },
};
</script>

<style >

.system {
  padding: 12px 2px;
}
.el-input-group__prepend {
  width: 65px !important;
}
.el-col {
  margin-bottom: 10px;
}
.el-row {
  margin-bottom: 20px;
}
</style>
