#ifndef _AW8896_H_
#define _AW8896_H_


/*
 * i2c transaction on Linux limited to 64k
 * (See Linux kernel documentation: Documentation/i2c/writing-clients)
 */

#define MAX_I2C_BUFFER_SIZE 65536
#define MAX_RAM_WRITE_BYTE_SIZE         128

#define AW8896_FLAG_DSP_START_ON_MUTE   (1 << 0)
#define AW8896_FLAG_SKIP_INTERRUPTS     (1 << 1)
#define AW8896_FLAG_SAAM_AVAILABLE      (1 << 2)
#define AW8896_FLAG_STEREO_DEVICE       (1 << 3)
#define AW8896_FLAG_MULTI_MIC_INPUTS    (1 << 4)
#define AW8896_FLAG_DSP_START_ON        (1 << 5)

#define AW8896_NUM_RATES                9

#define AW8896_MAX_REGISTER             0xff

#define AWINIC_DSP_I2C_WRITES
#define AW8896_DSP_FW_BASE              0x8c00
#define AW8896_DSP_CFG_BASE             0x8380
#define AW8896_DSP_FW_VER_BASE          0x0f80



enum aw8896_init {
	AW8896_INIT_ST = 0,
	AW8896_INIT_OK = 1,
	AW8896_INIT_NG = 2,
};

enum aw8896_chipid {
	AW8990_ID,
};

enum aw8896_mode_spk_rcv {
	AW8896_SPEAKER_MODE = 0,
	AW8896_RECEIVER_MODE = 1,
};

enum aw8896_dsp_fw_version {
	AW8896_DSP_FW_VER_D = 0,
	AW8896_DSP_FW_VER_E = 1,
};

enum aw8896_dsp_init_state {
	AW8896_DSP_INIT_STOPPED,        /* DSP not running */
	AW8896_DSP_INIT_RECOVER,        /* DSP error detected at runtime */
	AW8896_DSP_INIT_FAIL,           /* DSP init failed */
	AW8896_DSP_INIT_PENDING,        /* DSP start requested */
	AW8896_DSP_INIT_DONE,           /* DSP running */
	AW8896_DSP_INIT_INVALIDATED,    /* DSP was running, requires re-init */
};

enum aw8896_dsp_fw_state {
	AW8896_DSP_FW_NONE = 0,
	AW8896_DSP_FW_PENDING,
	AW8896_DSP_FW_FAIL,
	AW8896_DSP_FW_FAIL_COUNT,
	AW8896_DSP_FW_FAIL_REG_DSP,
	AW8896_DSP_FW_FAIL_PROBE,
	AW8896_DSP_FW_OK,
};

enum aw8896_dsp_cfg_state {
	AW8896_DSP_CFG_NONE = 0,
	AW8896_DSP_CFG_PENDING,
	AW8896_DSP_CFG_FAIL,
	AW8896_DSP_CFG_FAIL_COUNT,
	AW8896_DSP_CFG_FAIL_REG_DSP,
	AW8896_DSP_CFG_FAIL_PROBE,
	AW8896_DSP_CFG_OK,
};


struct aw8896 {
	struct regmap *regmap;
	struct i2c_client *i2c;
	struct snd_soc_component *component;
	struct mutex lock;
	int dsp_init;
	int dsp_fw_state;
	int dsp_cfg_state;
	int dsp_fw_len;
	int dsp_cfg_len;
	int dsp_fw_ver;
	int sysclk;
	u16 rev;
	int rate;
	struct device *dev;
	int pstream;
	int cstream;
	struct input_dev *input;

	int rst_gpio;
	int reset_gpio;
	int power_gpio;
	int irq_gpio;

#ifdef CONFIG_DEBUG_FS
	struct dentry *dbg_dir;
#endif
	u8 reg;

	unsigned int flags;
	unsigned int chipid;
	unsigned int init;
	unsigned int spk_rcv_mode;
};

struct aw8896_container {
	int len;
	unsigned char data[];
};

#endif
