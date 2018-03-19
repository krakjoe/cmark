--TEST--
CommonMark\Render Man Width
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
hello world
EOD
);

echo CommonMark\Render\Man($doc, CommonMark\Render\Normal, 4);
?>
--EXPECT--
.PP
hello
world


