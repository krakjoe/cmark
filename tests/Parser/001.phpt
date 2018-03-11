--TEST--
CommonMark\Parser
--FILE--
<?php
$parser = new CommonMark\Parser;

$parser->parse(<<<EOF
Title
=====

Body
EOF
);

$parser->finish();

echo "OK";
?>
--EXPECT--
OK
