    </table>
    <table id="result_table">
        <tr>
            <td> x </td>
            <td> y </td>
            <td> R </td>
            <td> Result </td>
            <td> time now </td>
            <td> time to work </td>
        </tr>
        <?php foreach ($_SESSION['history'] as $value) { ?>
            <tr>
                <td> <?php echo $value[0] ?> </td>
                <td> <?php echo $value[1] ?> </td>
                <td> <?php echo $value[2] ?> </td>
                <td> <?php echo $value[3] ?> </td>
                <td> <?php echo $value[4] ?> </td>
                <td> <?php echo $value[5] ?> </td>
            </tr>
        <?php } ?>
    </table>