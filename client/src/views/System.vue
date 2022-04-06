<template>
  <div class="system">
    <el-row :gutter="5">
      <el-col :span="24">
        <el-input placeholder="Router Wifi" v-model="ssid">
          <template slot="prepend">Wifi</template>
          <template slot="append">
            <el-button> OK </el-button>
          </template>
        </el-input>
      </el-col>
      <el-col :span="24">
        <el-input
          :show-password="true"
          placeholder="Router Password"
          v-model="sspw"
        >
          <template slot="prepend">Password</template>
          <template slot="append">
            <el-button> OK </el-button>
          </template>
        </el-input>
      </el-col>
    </el-row>
    
    <el-row :gutter="5">
      <el-col :span="24">
        <el-input placeholder="Access Point" v-model="apid">
          <template slot="prepend">Wifi AP</template>
          <template slot="append">
            <el-button> OK </el-button>
          </template>
        </el-input>
      </el-col>
      <el-col :span="24">
        <el-input
          :show-password="true"
          placeholder="Access Point Password"
          v-model="appw"
        >
          <template slot="prepend">Password</template>
          <template slot="append">
            <el-button> OK </el-button>
          </template>
        </el-input>
      </el-col>
    </el-row>
  </div>
</template>

<script>
export default {
  data: function () {
    return {
      ssid: "",
      sspw: "",
      apid: "",
      appw: "",
    };
  },
};
</script>

<style >
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
