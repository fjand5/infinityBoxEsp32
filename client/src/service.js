
let ServicePlugin =
{

  install: function (Vue) {

   
    Vue.prototype.$sendCommand = function () {
      let compt = this.compt
      this.$store.dispatch('sendCommand',
        {
          espKey: compt.espKey,
          espValue: this.clientValue
        }
      )
    }
  }
}
export default ServicePlugin