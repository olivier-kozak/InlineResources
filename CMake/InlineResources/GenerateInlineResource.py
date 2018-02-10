import argparse
import os


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("current_binary_dir")
    parser.add_argument("target")
    parser.add_argument("resource_file")
    parser.add_argument("inline_resource_template")

    args = parser.parse_args()

    inline_resources_dir = os.path.join(args.current_binary_dir, "{}_InlineResources".format(args.target))

    if not os.path.exists(inline_resources_dir):
        os.path.mkdir(inline_resources_dir)

    resource_name = os.path.basename(args.resource_file)

    with open(args.resource_file, "rb") as resource_file:
        bytes = resource_file.read()

        resource_content = ",\n        ".join(
            ", ".join(
                "0x{:02x}".format(ord(byte))
                for byte in bytes[i:i+18]
            )
            for i in range(0, len(bytes), 18)
        )

    with open(os.path.join(inline_resources_dir, "{}.cpp".format(resource_name)), "w") as output:
        with open(args.inline_resource_template, "r") as inline_resource_template:
            output.write(
                inline_resource_template.read()
                    .replace("@resource_content@", resource_content)
                    .replace("@resource_name@", resource_name)
            )


if __name__ == "__main__":
    main()
